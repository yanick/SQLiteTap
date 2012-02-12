.load sql_tap.ext

select plan(4);

select ok( 1, "this passes" );
select ok( 0, "this fails" );

create table puppies (
    name text,
    cuteness number
);

insert into puppies values ( 'lassie', 5 );
insert into puppies values ( 'spot', 7 );

select ok( cuteness >= 5, name || ' is darn cute' ) from puppies;
