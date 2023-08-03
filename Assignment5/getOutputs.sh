#! /usr/bin/expect -f

set timeout -1

spawn ssh student@65.0.124.36 

expect "*: "
send "Cryptonite\r"
expect "*: "
send "hesoyamo\r"
expect "*: "
send "5\r"
expect "*> "
send "go\r"
expect "*> "
send "wave\r"
expect "*> "
send "dive\r"
expect "*> "
send "go\r"
expect "*> "
send "read\r"

set fin_name "./inputs/inputs[lindex $argv 0].txt"
set fin [open "$fin_name" r]
set in_data [read $fin]

set fout_name "./outputs/raw/rawoutputs[lindex $argv 0].txt"
set fout [open $fout_name "w"]
 
# Read line by line
foreach line $in_data {
  # puts "$line\r"
  
  expect "> "
  send "$line\r"

  expect "$line\r"  # discard command echo
  expect "Slowly, a new text starts appearing on the screen. It reads ..."
  expect "\n\t\t*\n"  # match and save the result
  puts -nonewline $fout "$line\t$expect_out(0,string)\n"

  expect "Press c to continue> "
  send "c\r"
}
close $fin
close $fout

expect "*> "
send "exit\r"
