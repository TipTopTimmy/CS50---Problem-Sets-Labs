import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    #Gather data and populate table
    data = []
    symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])

    for symbol in range(len(symbols)):
        stock = {"symbol": None, "price": None, "quantity": None, "value": None}
        stock_quantity = db.execute("SELECT SUM(quantity) FROM transactions WHERE symbol = ?",symbols[symbol]["symbol"])
        stock["quantity"] = stock_quantity[0]["SUM(quantity)"]
        stock["symbol"] = symbols[symbol]["symbol"]
        stock_info = lookup(symbols[symbol]["symbol"])
        stock["price"] = stock_info["price"]
        stock["value"] = stock["price"]*stock["quantity"]
        print(stock)
        data.append(stock)
    #print(data)

    #Retrieve user cash available
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]["cash"]

    #Determine Portfolio Value
    key = "value"
    portfolio_value = 0
    for dicts in data:
        if key in dicts:
            portfolio_value += dicts[key]

    total = cash + portfolio_value
    return render_template("index.html", stocks = data, cash = cash, value = portfolio_value, total = total )



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        #Check for valid ticker input
        if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("Valid Ticker Entry Required", 400)

        #Check for valid share quantity
        share_quantity = request.form.get("shares")
        if not request.form.get("shares"):
            return apology("You must enter a valid number of shares", 400)

        #elif not share_quantity.replace(".","").isdigit():
            #return apology("Invalid quantity of shares", 400)

        elif not share_quantity.isdigit():
            return apology("You Cannot buy partial shares", 400)

        elif float(share_quantity) <=  0 :
            return apology("You cant buy negative shares", 400)

        #Perform stock purchase transaction
        #Check stock Price
        stock = lookup(request.form.get("symbol"))

        #Determine total cost of desired number of shares
        total_cost = stock["price"] * float(share_quantity)
        print("Total Cost is ", total_cost)

        #Determine user money available
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        print("USER CASH: ", user_cash[0]['cash'])

        #confirm there is enough money in user account to make purchase
        if total_cost > int(user_cash[0]["cash"]):
            return apology("Insufficient Funds", 403)
        difference = user_cash[0]["cash"]-total_cost
        #if sufficient funds exist complete purchase
        db.execute("UPDATE users SET cash=? WHERE id=?", difference, session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, price, quantity, cost, transaction_time)VALUES (?,?,?,?,?,datetime())", session["user_id"], stock["symbol"], stock["price"], share_quantity, total_cost)
        return redirect("/")
    else:
        return render_template("shop_stock.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
        #Gather data and populate table
    data = []
    symbols = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY transaction_time", session["user_id"])
    #print("DEBUG var symbols: ", symbols)
    for symbol in range(len(symbols)):
        stock = {"symbol": None, "price": None, "quantity": None, "value": None, "trans_type": None, "time": None}

        #Assign ticker symbol
        stock["symbol"] = symbols[symbol]["symbol"]

        #stock_info = lookup(symbols[symbol]["symbol"])
        stock["price"] = symbols[symbol]["price"]

        #determin quantity of stock bought/sold
        stock["quantity"] = symbols[symbol]["quantity"]

        #Determine if stock was bought or sold
        if stock["quantity"] < 0:
            stock["trans_type"] = "SELL"
        else:
            stock["trans_type"] = "BUY"

        #Determine transaction  price
        stock["value"] = stock["price"]* stock["quantity"]

        #Record transaction time/date
        stock["time"] = symbols[symbol]["transaction_time"]

        #print("DEBUG var stock: " stock)
        data.append(stock)
    #print(data)
    return render_template("history.html", stocks = data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        #Ensure user provides ticker symbol
        if not request.form.get("symbol"):
            return apology("must provide ticker symbol", 400)

        #Look up stock information
        result = lookup(request.form.get("symbol"))

        #Ticker not found
        if result == None:
            return apology("Ticker not found")

        return render_template("quote_result.html", name=result["name"], price=result["price"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif db.execute("SELECT username FROM users WHERE EXISTS(SELECT username FROM users WHERE username = ?)", request.form.get("username")):
            return apology("username exists", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        # Ensure Password and Confirm Password match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 400)

        # insert new user into database
        name = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, hash)


        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        #Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stock_symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    print(stock_symbols)
    symbols = []
    for symbol in stock_symbols:
        symbols.append(symbol["symbol"])
    print(symbols)
    if request.method == "POST":
        #make sure user is selling stock they own
        ticker = request.form.get("symbol")
        if not ticker:
            return apology("Select a valid stock symbol")
        if ticker not in symbols:
            return apology("You do not own this stock")

        #Gather share data to prep sale
        quantity = db.execute("SELECT SUM(quantity) FROM transactions WHERE symbol = ?", ticker)
        quantity = quantity[0]["SUM(quantity)"]
        print(quantity)

        #Ensure user inputs a number of shares
        if request.form.get("shares") == '':
            return apology("Enter a valid number of shares")

        #Ensure user has enough shares to sell desired amount
        shares = int(request.form.get("shares"))
        if shares <= 0 or shares > quantity:
            return apology("Enter a valid number of shares")
        stock = lookup(ticker)
        sale_amount = stock["price"]*quantity
        db.execute("INSERT INTO transactions (user_id, symbol, price, quantity, cost, transaction_time)VALUES (?,?,?,?,?,datetime())", session["user_id"], ticker, stock["price"], -shares, sale_amount)
        return redirect("/")
    else:
        print("DEBUG: ", symbols)
        return render_template("sell.html", options = symbols)
