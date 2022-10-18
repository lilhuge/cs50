select name from
people join directors on people.id = directors.person_id
join ratings on directors.movie_id = ratings.movie_id
where rating > 8.9 --write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.