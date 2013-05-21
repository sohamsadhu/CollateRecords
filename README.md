This repository tries to implement the group by clause in database. Each record is treated
as an associative array and then we try to group those in another associative array or
hash map.

Below is the problem statement that needs to be implemented. It is mostly written in 
Ruby style pseudo code.

The Ruby solution for this problem works. However, yet to fix the C++ version. The map 
tree built for group by takes on redundant branches. Got to fix that.

Question: Implement the following function in the programming language of your choice.

Function: collate_records(keys,records)
Re-organize an array of records by specified properties.
@param keys: An array of property names by which to collate the result.
@param records: An array of string tables (associative arrays).
@returns: a string table of tables (up to length(keys) deep) of all source records
collated as per keys. If keys is ['a', 'b'], the results will satisfy result[rec['a']][rec['b']] 
 = rec for all records in source.

Example in Ruby notation ([a,b] is an array; {k=>v} is a hash table):

collate_records(
  [ 'region', 'status' ], 
  [
    { 'name' => 'obj-1', 'status' => 'up', 'region' => 'us', ... },
    { 'name' => 'obj-2', 'status' => 'down', 'region' => 'us', ... },
    { 'name' => 'obj-3', 'status' => 'up', 'region' => 'eu', ... },
  ]
)

returns

{
  'us' => {
    'up' => { 'name' => 'obj-1', 'status' => 'up', 'region' => 'us', ... },
    'down' => { 'name' => 'obj-2', 'status' => 'down', 'region' => 'us', ... },
   },
  'eu' => { 
    'up' => { 'name' => 'obj-3', 'status' => 'up', 'region' => 'eu', ... },
   },


