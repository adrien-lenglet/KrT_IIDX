dstfolder = "../../common/src/Subtile/Macro"

def compile(target, dstfolder, itstart, itsize)
	puts("Building #{target}..")
	system("ruby ppduper.rb #{target} #{dstfolder} #{itstart} #{itsize}")
	puts("Done.")
end

["boost_pp_for_each.h", "dir_eachimpl.hpp", "boost_pp_eval.h"].each do |target|
	compile(target, dstfolder, 0, 256)
end

["seq_for_each.h"].each do |target|
	compile(target, dstfolder, 1, 256)
end