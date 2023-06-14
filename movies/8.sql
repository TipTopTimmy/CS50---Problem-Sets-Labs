SELECT name FROM people
JOIN stars ON people.id = stars.person_ID
JOIN movies ON stars.movie_id = movies.id
WHERE title = "Toy Story";


-- name -> people -> stars -> movie -> title
-- asset -> table -> table -> table -> asset