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
	File.open(input).each_line do |line|
		buf += expand(line, dict)
	end
	buf
end

def file_noext(path)
	path.delete_suffix(File.extname(path))
end

def compile_macro(file_path, output_folder)
	if file_path.nil? || output_folder.nil?
		raise "This program take 2 arguments"
	end

	folder_path = file_noext(file_path)
	system("rm -rf #{output_folder}/#{folder_path}")

	headers = "#pragma once\n\n"
	(0..255).each do |it|
		headers += "#{it_file(file_path, it)}\n"
	end
	File.new("#{output_folder}/#{file_path}_dupped.hpp", "w+").write(headers)
end

compile_macro(ARGV[0], ARGV[1])