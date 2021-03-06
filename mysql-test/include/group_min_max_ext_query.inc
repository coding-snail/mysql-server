# This query uses loose index scan.
let $hint = ;
let $check_query = $query $hint $cond;
eval EXPLAIN $check_query;
FLUSH STATUS;
eval $check_query;
SHOW STATUS LIKE 'handler_read%';
--disable_query_log
eval create table group_query $check_query;
--enable_query_log

# This query doesn't use loose index scan.
let $hint= IGNORE INDEX(k1) ;
let $check_query = $query $hint $cond;
--disable_query_log
eval create table no_group_query $check_query;
--enable_query_log

# Check result diffence between tables.
--let $diff_tables= test.group_query, test.no_group_query
--source include/diff_tables.inc
drop tables test.group_query, test.no_group_query;
