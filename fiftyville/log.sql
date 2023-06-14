-- Keep a log of any SQL queries you execute as you solve the mystery.

--read crime scene report
SELECT description FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2021 AND street = "Humphrey Street"
--Time of theft: 10:15am
--Location: Humphrey Street Bakery
-- 3 Witnesses

--Read witness report
SELECT * FROM interviews
WHERE day = 28 AND month = 7 AND year = 2021
--Witnesses: Ruth, Raymond, and maybe Eugene
--Security footage of parking lot,
--Prior to robbery theif withdrew money from ATM
--Just after robbery thief made a phone call to associate for accomplice to buy flight
--Taking earliest flight

--Determine ATM transaction details
SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
--+-----+----------------+------+-------+-----+----------------+------------------+--------+
--| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+
--| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
--| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
--| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
--| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
--| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
--| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
--| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
--| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+

--Bakery Security Logs
SELECT * FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 and minute > 15 AND minute < 26;
--+-----+------+-------+-----+------+--------+----------+---------------+
--| id  | year | month | day | hour | minute | activity | license_plate |
--+-----+------+-------+-----+------+--------+----------+---------------+
--| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
--| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
--| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
--| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
--| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
--| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
--| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
--| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
--+-----+------+-------+-----+------+--------+----------+---------------+

--Phone Calls
SELECT * FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60
--+-----+----------------+----------------+------+-------+-----+----------+
--| id  |     caller     |    receiver    | year | month | day | duration |
--+-----+----------------+----------------+------+-------+-----+----------+
--| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
--| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
--| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
--| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
--| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
--| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
--| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
--| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
--| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
--+-----+----------------+----------------+------+-------+-----+----------+

--Determine Fiftyville airport
SELECT id FROM airports
WHERE city = 'Fiftyville';
--+----+
--| id |
--+----+
--| 8  |
--+----+

--Determine Earliest Flight
SELECT * from flights
WHERE day = 29 AND month = 7 AND year = 2021
ORDER BY hour, minute
LIMIT 1;
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
---+----+-------------------+------------------------+------+-------+-----+------+--------+

SELECT city FROM airports
WHERE id = (SELECT destination_airport_id FROM flights
WHERE year = 2021 AND day = 29
ORDER BY hour, minute
LIMIT 1);

--Determine Passengers
SELECT * FROM passengers
WHERE flight_id = (SELECT id from flights
WHERE day = 29 AND month = 7 AND year = 2021
ORDER BY hour, minute
LIMIT 1);

--+-----------+-----------------+------+
--| flight_id | passport_number | seat |
--+-----------+-----------------+------+
--| 36        | 7214083635      | 2A   |
--| 36        | 1695452385      | 3B   |
--| 36        | 5773159633      | 4A   |
--| 36        | 1540955065      | 5C   |
--| 36        | 8294398571      | 6C   |
--| 36        | 1988161715      | 6D   |
--| 36        | 9878712108      | 7A   |
--| 36        | 8496433585      | 7B   |
--+-----------+-----------------+------+

--obtain person_id from atm transactions
SELECT * FROM bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");

--determine theif
SELECT * FROM people
JOIN bank_accounts on people.id = bank_accounts.person_id
WHERE account_number IN (SELECT account_number FROM atm_transactions
    WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")
AND phone_number IN (SELECT caller FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60)
AND passport_number IN (SELECT passport_number FROM passengers
    WHERE flight_id = (SELECT id from flights
        WHERE day = 29 AND month = 7 AND year = 2021
        ORDER BY hour, minute
        LIMIT 1))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 and minute > 15 AND minute < 26);

--Determine accomplice phone number
SELECT name FROM people
WHERE phone_number = (SELECT receiver FROM phone_calls
WHERE caller =(SELECT phone_number FROM people WHERE name = "Bruce" AND month = 7 AND DAY = 28 AND year = 2021));

