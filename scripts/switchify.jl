using Maple

maps = filter(x -> endswith(x, ".bin"), readdir("."))

for mapFile in maps
  println("loading map: $(mapFile)")
  mapleMap = loadMap(mapFile)
  correctPackage = mapFile[1:end-4]
  println("map loaded") 
  println("package: $(mapleMap.package)")
  println("correct package: $(correctPackage)")
  mapleMap.package = correctPackage
  println("package changed to $(mapleMap.package)")
  encodeMap(mapleMap, mapFile)
  println("saved fixed map: $(mapFile)")
end
