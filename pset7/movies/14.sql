Create table j_film as

select title, movie_id from
movies join stars on movies.id = stars.movie_id
join people on stars.person_id = people.id
where name = "Johnny Depp"; 

create table h_film as
select movie_id from
movies join stars on movies.id = stars.movie_id
join people on stars.person_id = people.id
where name = "Helena Bonham Carter";

select title from j_film join h_film on j_film.movie_id = h_film.movie_id;
