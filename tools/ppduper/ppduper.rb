def expand(str, dict)
	i = 0
	while i < str.size
		if str[i] == "|"
			i += 1
			start = i
			while str[i] != "|"
				i += 1
			end
			id = str[start, i - start]
			str = str[0, start - 1] + dict[id] + str[i + 1, str.size]
			i = 0
		end
		i += 1
	end
	str
end

def it_file(input, output, it)
	buf = ""
	dict = {}
	dict["it"] = it.to_s
	File.open(input).each_line do |line|
		buf += expand(line, dict)
	end
	File.new(output, "w+").write(buf)
end

def file_noext(path)
	path.delete_suffix(File.extname(path))
end

file_path = ARGV[0]
folder_path = file_noext(file_path)
system("rm -rf #{folder_path}")
system("mkdir #{folder_path}")

headers = "#pragma once\n\n"
(0..255).each do |it|
	filename = "#{folder_path}/it_#{it.to_s(16)}.hpp"
	it_file(file_path, filename, it)
	headers += "#include \"#{filename}\"\n"
end
File.new("#{file_path}_dupped.hpp", "w+").write(headers)