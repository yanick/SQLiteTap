use strict;
use warnings;

use Test::More tests => 4;

use DBI;

my $dbh = DBI->connect( 'dbi:SQLite:test.db' );

$dbh->sqlite_enable_load_extension(1);
#$dbh->do("select load_extension('/home/yanick/work/perl-modules/SQLiteTAP/sqlitetap/sql_tap.ext')");
$dbh->do("select load_extension('sql_tap.ext')");

my $sth = $dbh->prepare( 'select plan(4)' );
$sth->execute;
is $sth->fetchrow => '1..4', "plan";

$sth = $dbh->prepare( 'select ok( 1, "this passes" )' );
$sth->execute;
is $sth->fetchrow => 'ok 1 - this passes', "ok with desc";

$sth = $dbh->prepare( 'select ok( 0, "this fails" )' );
$sth->execute;
is $sth->fetchrow => 'not ok 2 - this fails', "not ok with desc";
