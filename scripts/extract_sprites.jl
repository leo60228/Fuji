using Cairo
using Maple
using Glob
import JSON

include("extract_sprites_images.jl")
include("extract_sprites_meta.jl")

atlases = ARGS[1]
atlas = ARGS[3]
dest = "$(ARGS[2])/$(atlas)"

mkpath(dest)

dataFiles = vcat(glob("$(atlas)/*.data", atlases), glob("$(atlas)?.data", atlases))

sprites = Dict{String, Sprite}()
encodedSprites = Dict{String, Any}()

for data in dataFiles
  png = "$(dest)/$(splitext(basename(data))[1]).png"
  dumpSprites(data, png)
  sprites = merge(sprites, loadSprites("$(atlases)/$(atlas).meta", png))
end

println(join(keys(sprites), ", "))

for spriteName in keys(sprites)
  sprite = sprites[spriteName]
  
  originalSurface = sprite.surface

  @printf "%s => height = %d, width = %d, offsetX = %d, offsetY = %d, x = %d, y = %d, realWidth = %d, realHeight = %d, filename = %s\n" spriteName sprite.height sprite.width sprite.offsetX sprite.offsetY sprite.x sprite.y sprite.realWidth sprite.realHeight sprite.filename

  rawSpriteSurface = CairoARGBSurface(sprite.width, sprite.height)
  spriteSurface = CairoARGBSurface(sprite.width, sprite.height)

  ctx = CairoContext(rawSpriteSurface)

  set_source_surface(ctx, originalSurface, -sprite.x, -(sprite.y/2))

  paint(ctx)

  newCtx = CairoContext(spriteSurface)
  scale(newCtx, 1, 2)
  set_source_surface(newCtx, rawSpriteSurface, 0, 0)

  paint(newCtx)

  write_to_png(spriteSurface, "$(dest)/$(spriteName).png")

  spriteJson = Dict{String, Any}()

  spriteJson["width"] = sprite.width
  spriteJson["height"] = sprite.height
  spriteJson["offsetX"] = sprite.offsetX
  spriteJson["offsetY"] = sprite.offsetY
  spriteJson["x"] = sprite.x
  spriteJson["y"] = sprite.y
  spriteJson["realWidth"] = sprite.realWidth
  spriteJson["realHeight"] = sprite.realHeight
  spriteJson["filename"] = sprite.filename

  encodedSprites[spriteName] = spriteJson
end

json = JSON.json(encodedSprites)

open("$(dest)/$(atlas).json", "w") do f
    write(f, json)
end
