import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from finance.helpers_0 import apology, login_required, lookup, usd

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

"""
 _____ _   _______ _______   __
|_   _| \ | |  _  \  ___\ \ / /
  | | |  \| | | | | |__  \ V /
  | | | . ` | | | |  __| /   \
 _| |_| |\  | |/ /| |___/ /^\ \
 \___/\_| \_/___/ \____/\/   \/

"""
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    return render_template("index.html")

"""
______ _   ___   __
| ___ \ | | \ \ / /
| |_/ / | | |\ V /
| ___ \ | | | \ /
| |_/ / |_| | | |
\____/ \___/  \_/

"""
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        #Check for valid ticker input
        if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("Valid Ticker Entry Required", 403)

        #Check for valid share quantity
        share_quantity = int(request.form.get("shares"))
        if not request.form.get("shares") or share_quantity < 0:
            return apology("Invalid quantity of shares", 403)

        #Perform stock purchase transaction
        #Check stock Price
        stock = lookup(request.form.get("symbol"))

        #Determine total cost of desired number of shares
        total_cost = stock["price"] * share_quantity
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
        return render_template("index.html")
    else:
        return render_template("shop_stock.html")

"""
 _   _ _____ _____ _____ _____________   __
| | | |_   _/  ___|_   _|  _  | ___ \ \ / /
| |_| | | | \ `--.  | | | | | | |_/ /\ V /
|  _  | | |  `--. \ | | | | | |    /  \ /
| | | |_| |_/\__/ / | | \ \_/ / |\ \  | |
\_| |_/\___/\____/  \_/  \___/\_| \_| \_/

"""
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")

"""
 _     _____ _____ _____ _   _
| |   |  _  |  __ \_   _| \ | |
| |   | | | | |  \/ | | |  \| |
| |   | | | | | __  | | | . ` |
| |___\ \_/ / |_\ \_| |_| |\  |
\_____/\___/ \____/\___/\_| \_/

"""
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
"""
 _     _____ _____ _____ _   _ _____
| |   |  _  |  __ \  _  | | | |_   _|
| |   | | | | |  \/ | | | | | | | |
| |   | | | | | __| | | | | | | | |
| |___\ \_/ / |_\ \ \_/ / |_| | | |
\_____/\___/ \____/\___/ \___/  \_/
"""
@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

"""
 _____ _   _ _____ _____ _____
|  _  | | | |  _  |_   _|  ___|
| | | | | | | | | | | | | |__
| | | | | | | | | | | | |  __|
\ \/' / |_| \ \_/ / | | | |___
 \_/\_\\___/ \___/  \_/ \____/

"""
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        #Ensure user provides ticker symbol
        if not request.form.get("search"):
            return apology("must provide ticker symbol", 403)

        #Look up stock information
        result = lookup(request.form.get("search"))

        #Ticker not found
        if result == None:
            return apology("Ticker not found")

        return render_template("quote_result.html", name=result["name"], price=result["price"])

    else:
        return render_template("quote.html")

"""
______ _____ _____ _____ _____ _____ ___________
| ___ \  ___|  __ \_   _/  ___|_   _|  ___| ___ \
| |_/ / |__ | |  \/ | | \ `--.  | | | |__ | |_/ /
|    /|  __|| | __  | |  `--. \ | | |  __||    /
| |\ \| |___| |_\ \_| |_/\__/ / | | | |___| |\ \
\_| \_\____/ \____/\___/\____/  \_/ \____/\_| \_|

"""
@app.route("/register", methods=["GET", "POST"])
def register():
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

        # Ensure password was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 403)

        # Ensure Password and Confirm Password match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 403)

        # insert new user into database
        name = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, hash)


        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        #Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")

"""
 _____ _____ _      _
/  ___|  ___| |    | |
\ `--.| |__ | |    | |
 `--. \  __|| |    | |
/\__/ / |___| |____| |____
\____/\____/\_____/\_____/

"""
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
