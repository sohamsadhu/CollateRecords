def make_records
  rec1 = { 'name' => 'obj-1', 'status' => 'up', 'region' => 'us' }
  rec2 = { 'name' => 'obj-2', 'status' => 'down', 'region' => 'eu' }
  rec3 = { 'name' => 'obj-3', 'status' => 'up', 'region' => 'eu' }
  rec4 = { 'name' => 'obj-4', 'status' => 'down', 'region' => 'us' }
  records = [ rec1, rec2, rec3, rec4 ]
end

def collate_helper( keys, record ) 
  stack = []
  keys.each do |i|
    stack.push( record[ i ] )
  end
  # Credit for the following line Marcos Crispino 
  # http://stackoverflow.com/users/135050/marcos-crispino
  stack.reverse.inject( record ) { |a, n| { n => a }}
end

def collate_records( keys, records )
  result = []
  records.each do |i|
    result.push( collate_helper( keys, i ))
  end
  # Credit for following line Glenn McDonald and Alex Kliuchnikau 
  # http://stackoverflow.com/users/7919/glenn-mcdonald
  # http://stackoverflow.com/users/158689/alex-kliuchnikau
  result.reduce({}) { |h, r| h.merge(r) {|key, h_val, r_val| h_val.merge r_val } }
end

def main
  collate_records(['region', 'status'], make_records)
end
