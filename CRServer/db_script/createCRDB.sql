create database crdb;

use crdb;

create table accountadmin(username char(20), password char(20), phonenum char(20), email char(128), nickname char(20), sort int(4));

create table accountuser(username char(20), password char(20), phonenum char(20), email char(128), nickname char(20), sort int(4));

create table products(uuid char(128), title char(100), price char(50), description char(255), images char(255), keyword char(255), status tinyint(1));
