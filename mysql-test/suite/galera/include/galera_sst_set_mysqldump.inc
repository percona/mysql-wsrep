#
# Set all the variables required for the SST to be performed via mysqldump
#

--echo Setting SST method to mysqldump ...

--connection node_1
# We need a user with a password to perform SST, otherwise we hit LP #1378253
GRANT ALL PRIVILEGES ON *.* TO 'sst' IDENTIFIED BY 'sst';

--let $wsrep_sst_auth_orig = `SELECT @@wsrep_sst_auth`
SET GLOBAL wsrep_sst_auth = 'sst:sst';

--connection node_2
--let $wsrep_sst_method_orig = `SELECT @@wsrep_sst_method`
--let $wsrep_sst_receive_address_orig = `SELECT @@wsrep_sst_receive_address`

--disable_query_log
# Set wsrep_sst_receive_address to the SQL port
--eval SET GLOBAL wsrep_sst_receive_address = '127.0.0.2:$NODE_MYPORT_2';
--enable_query_log
SET GLOBAL wsrep_sst_method = 'mysqldump';
