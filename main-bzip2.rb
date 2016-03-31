#!/usr/bin/env ruby

require 'fileutils'
require 'rubygems'
require 'json'
require 'tempfile'

if __FILE__ == $0
  if ARGV.length == 0 then
    return
  end
  puts ARGV[0]
  dir = File.dirname(ARGV[0])
  base = File.basename(ARGV[0], ".osm.bz2")
  temp = Tempfile.new('edge')
  puts format("bzip2 -dck %s | ./extract_edge > %s", ARGV[0], temp.path)
  system(format("bzip2 -dck %s | ./extract_edge > %s", ARGV[0], temp.path))
  puts format("bzip2 -dck %s | ./extract_vertex %s > %s/%s.graph", ARGV[0], temp.path, dir, base)
  system(format("bzip2 -dck %s | ./extract_vertex %s > %s/%s.graph", ARGV[0], temp.path, dir, base))
end
