select distinct(title) from movies 

where id in (select movie_id from
movies join stars on movies.id = stars.movie_id
join people on stars.person_id = people.id
where name = "Helena Bonham Carter")

and id in (select movie_id from
movies join stars on movies.id = stars.movie_id
join people on stars.person_id = people.id
where name = "Johnny Depp");


--where name = "Helena Bonham Carter";--write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.