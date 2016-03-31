#!/usr/bin/env ruby

require 'fileutils'
require 'rubygems'
require 'json'
require 'tempfile'

if __FILE__ == $0
  if ARGV.length == 0 then
    return
  end
  dir = File.dirname(ARGV[0])
  base = File.basename(ARGV[0], ".osm")
  temp = Tempfile.new('edge')
  puts format("./extract_edge < %s > %s", ARGV[0], temp.path)
  system(format("./extract_edge < %s > %s", ARGV[0], temp.path))
  puts format("./extract_vertex %s < %s > %s/%s.graph", temp.path, ARGV[0], dir, base)
  system(format("./extract_vertex %s < %s > %s/%s.graph", temp.path, ARGV[0], dir, base))
end
