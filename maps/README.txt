# [MAP FORMAT]
# With examples
# 
# Vertices_number: "V + space + number"
# Vertex:
# Y X
# Space(s) between values
#
V  6
0  0
0  15
15 0
15 15
0  30
15 30

# Emtpy line after vertices declaration
# Sectors_number: "S + space + number"
# Sectors:
# [floor_height floor_slope floor_texture] 
# [ceiling_height ceiling_slope ceiling_texture]
# (vertex numbers in clockwise order)
# (neighbors numbers in clockwise order) ('-1' = no neighbor)
# (textures numbers)
# light value between 0 and 100
# Space(s) between every section
#
S  2
[0  0  5]  [12 0 4]   (0 1 3 2)  (-1  1  -1 -1) (0  1  2  3) 70
[2  0  4]  [14 0 4]   (1 4 5 3)  (-1  -1  -1  0) (0  1  2  3) 95

# Emtpy line after sectors declaration
# Objects_number: "O + space + number"
# Object:
# [y x z angle] [sprite_number scale]
# Space(s) between every section
# Angle is ignored if the sprite is not oriented
#
O  1
[7.5 7.5 1 45] [0 50]

# Emtpy line after objects declaration
# Enemies_nmber: "E + space + number"
# Enemies:
# [y x z angle] [sprite_number scale] [health speed damage]
# spaces between each section
# speed should be between 0 and 1 (0 being static and 1 super fast)
#
E 1
[5 5 5 0] [1 50] [50 0.3 15]

# Empty lin after enemies declaration
# Player:
# Y X angle
# One space between values
#
1  1   45
