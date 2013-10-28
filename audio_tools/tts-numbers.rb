#!/usr/bin/env ruby

require 'FileUtils'

1.upto 1000 do |i|
  system "wget 'http://tts-api.com/tts.mp3?q=#{i}' -O #{"%08d" % i}.mp3"
end

