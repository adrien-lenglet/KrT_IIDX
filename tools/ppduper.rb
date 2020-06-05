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

def it_file(input, it)
	buf = ""
	dict = {}
	dict["it"] = it.to_s
	dict["it + 1"] = (it + 1).to_s
	dict["it - 1"] = (it - 1).to_s
	File.open(input).each_line do |line|
		buf += expand(line, dict)
	end
	buf
end

def file_noext(path)
	path.delete_suffix(File.extname(path))
end

def compile_macro(file_path, output_file, itstart, itsize)
	if file_path.nil? || output_file.nil? || itstart.nil? || itsize.nil?
		raise "This program take 2 arguments"
	end

	itstart = itstart.to_i
	itsize = itsize.to_i
	folder_path = file_noext(file_path)

	headers = "#pragma once\n\n"
	(itstart..(itsize - 1)).each do |it|
		headers += "#{it_file(file_path, it)}\n"
	end
	File.new(output_file, "w+").write(headers)
end

compile_macro(ARGV[0], ARGV[1], ARGV[2], ARGV[3])