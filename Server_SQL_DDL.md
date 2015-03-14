# Table Definition #

  * user(account\_id, account, password, account\_type, ipaddress, logged\_in)

> create table user(account\_id int, account varchar(20), password varchar(25), account\_type int, ipaddress, varchar(20), logged\_in varchar(5), primary key(account\_id));

  * problem(problem\_id, path\_description, correct\_input\_filename, correct\_output\_filename, time\_limit)

> create table problem(problem\_id int, path\_description VARCHAR(50), correct\_input\_filename varchar(50), correct\_output\_filename varchar(50), primary key(problem\_id));

  * submission(run\_id, account\_id, problem\_id, lang, path\_code, judge\_result)

> create table submission(run\_id int, account\_id int, problem\_id int, lang varchar(10), path\_code varchar(50), judge\_result varchar(25), primary key(run\_id), foreign key(account\_id) references user, foreign key(problem\_id) references problem);

  * clarification(clar\_id, account\_id, msg, result, private\_byte)

> create table clarification(clar\_id int, account\_id int, msg varchar(100), result varchar(100), private\_byte int, primary key(clar\_id), foreign key(account\_id) references user);

  * scoreboard(account\_id, time, score)

> create table scoreboard(account\_id int, time int, score int, primary key(account\_id), foreign key(account\_id) references user);
