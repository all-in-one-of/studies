# MySQL & RDBMS

A Relational Database is a collection of data organized into tables. Tables are comprised of vertical columns
and horiztonal rows. Each column is a set of data of the same type. Each row represents a structured data item in the table

SQL is a database computer language used to manage data in a database

a schema of a databases is a structure defined in a formal language

a trigger is procedural code that is executed in response to specific events on a table

a transaction is an atomic unit of operations in a database, the effects of the SQL statements in
a transaction can be either committed to the databse or rolled back.

A SQL result set is a set of rows returned from a SELECT statement. It contains meta information about the query
including column names, size of columns, and column data types.

an index is a data structure used to make data retrieval more effecient

## Managing users

### Create new user
	CREATE USER 'username'@localhost IDENTIFIED BY 'password';

### Change user password
	ALTER USER 'userName'@localhost IDENTIFIED BY 'new_password';

### Grant privleges
	GRANT ALL PRIVILEGES ON dbname.tablename TO 'username'@localhost;

	FLUSH PRIVILEGES; #reloads privileges

### Show existing users
Users are stored in a table called mysql.user

	SELECT user, host FROM mysql.user

see other user columns

	SHOW columns FROM mysql.user;

## SQL Queries

###Basic query on a table named city:

	SELECT Id, Name, Population, From City 

###Limit Results, offset entries by 5 and show up to 10th entry

	SELECT Id, Name, Population FROM City LIMIT 5, 10;

###use WHERE to filter results

	SELECT Id, Name, Population FROM City
	WHERE Population > 10000;

	SELECT Id, Name, Population FROM City
	WHERE Population = (SELECT Min(Population) FROM City);

	SELECT Name FROM city WHERE Name LIKE 'Kal%';

	SELECT Name, Population FROM city WHERE ID IN (5, 23, 432, 2021);

	SELECT * FROM city WHERE Name = 'Bratislava'

###order data:

	SELECT Name, Population FROM city
    ORDER BY Population DESC LIMIT 10;

	SELECT Name, Population FROM city
    ORDER BY Name LIMIT 10;


###group data:
	
	# select all cities in district 'New York'
	# return a set with the district name and sum of population
	SELECT District, SUM(Population) FROM city
    WHERE District = 'New York' GROUP BY District;

	# group cities in the USA by district with a population over 3 million
	SELECT District, SUM(Population) FROM city
	WHERE CountryCode = 'USA' GROUP BY District
	HAVING SUM(Population) > 3000000;

When we work with groups of data, we use the HAVING clause instead of the WHERE clause.

### Creating Tables

#### Simplified syntax for creating tables
	CREATE TABLE [IF NOT EXISTS] table_name(
	    column_list
	) ENGINE=storage_engine

#### column syntax
	column_name data_type(length) [NOT NULL] [DEFAULT value] [AUTO_INCREMENT]

#### example

	CREATE TABLE IF NOT EXISTS tasks (
	    task_id INT AUTO_INCREMENT,
	    title VARCHAR(255) NOT NULL,
	    start_date DATE,
	    due_date DATE,
	    status TINYINT NOT NULL,
	    priority TINYINT NOT NULL,
	    description TEXT,
	    PRIMARY KEY (task_id)
	)  ENGINE=INNODB;

### Creating, Updating, Inserting, & Deleting Data

	# update HeadOfState value for 'United States' in the table country
	UPDATE country SET HeadOfState = 'Donald Trump'
    WHERE Name = 'United States';
	
	# Create a temporary table in memory from the top ten cities
	CREATE TABLE toptencities engine=MEMORY SELECT * FROM city LIMIT 10;

	# Remove cities with id values of (1, 3, 4, 7)
	DELETE FROM toptencities WHERE ID IN (1, 3, 4, 7);

	# empty the toptencities table
	TRUNCATE TABLE toptencities;
	
	# insert a new city
	INSERT INTO toptencities VALUES(1, 'Kabul', 'AFG', 'Kabol', 1780000)

	# remove the table
	DROP TABLE toptencities

## Data Types
Columns can be defined by one of the following four data types:

- Numeric
- Date & time
- String
- JSON

### Numeric Sub data types
- Integers
	- TINYINT
	- SMALLINT
	- MEDIUMINT
	- INTEGER
	- BIGINT
- Floating points
	- FLOAT
	- DOUBLE
	- DECIMAL
### Date and Time
- Date
- Time
- Datetime
- Year
- Timestamp

### Strings
- CHAR
- VARCHAR
- BINARY
- VARBINARY
- BLOB
- TEXT
- ENUM
- SET

### JSON - Javascript Object Notation

## Joins

The SQL JOIN clause combines records from two or more tables in a database. There are basically two types of joins: INNER and OUTER.

If two tables have columns with the same name they can be used as the relationship column and the USING clause can be used in joins. Otherwise we would use the ON clause, eg ON Table1.ColName = Table2.ColName

	SELECT Name, Day FROM Customers JOIN Reservations ON Customers.CustomerId = Reservations.CustomerId

	SELECT Name, Day FROM Customers JOIN Reservations USING (CustomerId)

[JOIN ON vs JOIN USING](https://stackoverflow.com/a/11367066/7298096) - Mostly syntatic sugar. JOIN ON offers more flexibility. 

## Functions

Home Contents Subscribe Previous Next
MySQL functions
In this part of the MySQL tutorial, we will cover MySQL built-in functions.

MySQL built-in functions can be categorized into several groups.

- Mathematical functions
- Aggregate functions
- String functions
- Date and time functions
- System Functions

## Views

A view is a pseudo table. It is a stored query which looks like a table. And it can be referenced like a table.

A view consists of a stored query accessible as a virtual table composed of the result set of a query. Unlike ordinary tables a view does not form part of the physical schema. It is a dynamic, virtual table computed or collated from data in the database.

## Transactions
If your database storage engine is ACID compliant (Atomicity, Consistency, Isolation, Durability), such as InnoDB. Your SQL Statements can be preformed as transactions. The effects of all the SQL statements in a transaction can either be fully committed or rolled back.

If you preform SQL operations in a transaction without committing them the effects will only be visible on your current connection to the database server. 

## MySQL Stored Routines

Stored procedures are called with the CALL statement. They do not return values. Stored functions return values. And are used with the SELECT statement.