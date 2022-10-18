select name from
people join stars on people.id = stars.person_id
where movie_id in (select movie_id from 
stars join people on stars.person_id = people.id
where name = "Kevin Bacon" and birth = 1958) and name != "Kevin Bacon";--write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.