create database if not exists `file_info`;
use file_info;
create table directory (
  path varchar(255) not null,
  subdirectories varchar(100) not null,
  files varchar(100) not null,
  size varchar(100) not null,
  primary key (path)
);
insert into directory values ('E:/', 1, 1, '1.0 KB');