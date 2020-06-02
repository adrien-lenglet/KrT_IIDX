dstfolder = "../../common/src/Subtile/Macro"

#["boost_pp_for_each.h", "dir_eachimpl.hpp", "class_impl_rc.hpp"].each do |target|
["class_impl_rc.hpp", "boost_pp_expr_if.h", "boost_pp_expr_iif.h", "boost_pp_bool.h"].each do |target|
		puts("Building #{target}..")
	system("ruby ppduper.rb #{target} #{dstfolder}")
	puts("Done.")
end
