require 'xcodeproj'

#ruby sortGroup.rb openGLDemo.xcodeproj openGLDemo
projectPath = ARGV[0]
targetName = ARGV[1]
if !projectPath
#    projectPath = "#{Dir.pwd}/../LightGameSDKDemo/LightGameSDKDemo.xcodeproj"
    puts "请输入工程路径"
    exit 1
end
if !targetName
#    targetName = "LightGameSDKDemo"
    puts "请输入工程Target"
    exit 1
end

# 获取目标对象
def getTargetWithName(project, targetName)
    project.native_targets.each do |target|
        if target.name == targetName
            return target
        end
    end
end

def sort_by_type_and_name(group)
	children = group.children
	children.sort! do |x, y|
	    if x.isa == 'PBXGroup' && !(y.isa == 'PBXGroup')
			-1
	    elsif !(x.isa == 'PBXGroup') && y.isa == 'PBXGroup'
	      	1
	    elsif x.display_name && y.display_name
	      	extname_x = File.extname(x.display_name)
	      	extname_y = File.extname(y.display_name)
            sourceType = ['.h', '.m', '.hpp', '.cpp', '.mm']
            if (extname_x != extname_y) && !((sourceType.include? extname_x) && (sourceType.include? extname_y))
	        	extname_x <=> extname_y
	      	else
	        	result = File.basename(x.display_name.downcase, '.*') <=> File.basename(y.display_name.downcase, '.*')
	        	if result.zero?
	          		File.extname(x.display_name.downcase) <=> File.extname(y.display_name.downcase)
	        	else
	          		result
	        	end
	      	end
	    else
	     	0
	    end
	end
end

def sort_recursively_by_type_and_name(group)
	children = group.children
	groups = children.select { |obj| obj.isa == 'PBXGroup' }
	groups.each do |g|
		sort_recursively_by_type_and_name(g)
	end
	sort_by_type_and_name(group)
end

# 排序主工程
project = Xcodeproj::Project.open(projectPath)
group = project.main_group
sort_recursively_by_type_and_name(group)

# 排序子工程
subProjects =  group.children.select { |obj| File.extname(obj.display_name) == '.xcodeproj' }
subProjects.each do |item|
	if item.real_path
		subProject = Xcodeproj::Project.open(item.real_path)
		if subProject
			sort_recursively_by_type_and_name(subProject.main_group)
			subProject.save
		end
	end
end

project.save
