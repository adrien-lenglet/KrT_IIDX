puts "{"
File.open("glfw_keys.txt").read.split("\n").each do |line|
	next if line.split("/*").first == ""
	tokens = line.split(" ")
	next if tokens.size == 0

	puts "\t{\"#{tokens[1].delete_prefix("GLFW_")}\", #{tokens[1]}}, "
end
puts "};"