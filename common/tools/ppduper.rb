def eval_it(it, expr)
	eval(expr).to_s
end

def expand(str, it)
	i = 0
	while i < str.size
		if str[i] == "|"
			i += 1
			start = i
			while str[i] != "|"
				i += 1
			end
			id = str[start, i - start]
			str = str[0, start - 1] + eval_it(it, id) + str[i + 1, str.size]
			i = 0
		end
		i += 1
	end
	str
end

def it_file(input, it)
	buf = ""
	File.open(input).each_line do |line|
		buf += expand(line, it)
	end
	buf
end

def file_noext(path)
	path.delete_suffix(File.extname(path))
end

def compile_macro(file_path, output_file, itstart, itsize)
	itstart = itstart.to_i
	itsize = itsize.to_i
	folder_path = file_noext(file_path)

	headers = "#pragma once\n\n"
	(itstart..(itsize - 1)).each do |it|
		headers += "#{it_file(file_path, it)}\n"
	end
	File.new(output_file, "w+").write(headers)
end

itstart = 0
itsize = nil

(0..(ARGV.size - 1)).each do |i|
	if ARGV[i] == "-I"
		itstart = ARGV[i + 1].to_i
	end
	if ARGV[i] == "-N"
		itsize = ARGV[i + 1].to_i
	end
end

input = ARGV[0]
output = ARGV[1]

if input.nil? || output.nil?
	raise "This program take at least 2 arguments ([input] [output])"
end

outbase = File.basename(output)
if itsize.nil? && outbase[0, 3] == "it_"
	itsize = outbase.split(".")[0].split("it_")[1].to_i
end

compile_macro(input, output, itstart, itsize)