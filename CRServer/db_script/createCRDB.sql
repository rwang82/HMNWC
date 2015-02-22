create database crdb;

use crdb;

create table accountadmin(username char(20), password char(20), phonenum char(20), email char(128), nickname char(20), sort int(4), attetioned int(4), attetion int(4), published int(4));

create table accountuser(username char(20), password char(20), phonenum char(20), email char(128), nickname char(20), sort int(4), attetioned int(4), attetion int(4), published int(4));

create table products(publisher char(20), uuid char(128), title char(100), price char(50), description char(255), sort int(4), udsort char(20), images char(255), keyword char(255), status tinyint(1));

create table attetioninfo(attetionfrom char(20), attetionto char(20));
