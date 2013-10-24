#!/usr/bin/env ruby

abort "Usage: #{__FILE__} serial_port" if ARGV.length != 1

require 'rubygems'
require 'serialport'

sp = SerialPort.new ARGV[0], 9600
sp.read_timeout = 50

while TRUE do
  recv = sp.read()
  puts recv.each_byte.map { |b|
    b.to_s(16).rjust(2, '0') + ' '
  }.join if recv.length > 0
end

