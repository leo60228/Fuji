using FixedPointNumbers
using ColorTypes

struct TextureArray <: AbstractArray{RGBA,2}
    backing::Array{RGBA{N0f8},2}
end

Base.size(A::TextureArray)::Tuple{Int, Int} = (size(A.backing)[1]*2, floor(size(A.backing)[2]/2))
Base.getindex(A::TextureArray, I::Vararg{Int, N}) where N = A.backing[Int(ceil(I[1] / 2)), iseven(I[1]) ? I[2] + size(A)[2] : I[2]]
Base.setindex!(A::TextureArray, v::RGBA{N0f8}, I::Vararg{Int, 2}) = (A.backing[floor(I[1] / 2, iseven(I[1]) ? I[2] + size(A)[1] : I[2])] = v)
Base.IndexStyle(::Type{<:TextureArray}) = IndexCartesian()

gray(c) = RGBA{N0f8}(c, c, c, 1)

testtexture() = TextureArray(gray.(reshape(0:15, 4, 4) ./ 15))