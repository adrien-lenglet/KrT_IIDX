dstfolder = "../../common/src/Subtile/Macro"

["boost_pp_for_each.h", "dir_eachimpl.hpp"].each do |target|
	puts("Building #{target}..")
	system("ruby ppduper.rb #{target} #{dstfolder}")
	puts("Done.")
end
