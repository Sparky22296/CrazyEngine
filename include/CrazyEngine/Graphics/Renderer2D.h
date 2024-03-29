#ifndef CRAZYENGINE_GRAPHICS_RENDERER2D_H_
#define CRAZYENGINE_GRAPHICS_RENDERER2D_H_

#include <cstdint>
#include <array>

#include "CrazyEngine/Graphics/RendererAPI.h"
#include "CrazyEngine/Graphics/Shader.h"
#include "CrazyEngine/Graphics/Vertex.h"
#include "CrazyEngine/Graphics/Buffers.h"
#include "CrazyEngine/Graphics/VertexArray.h"
#include "CrazyEngine/Graphics/Texture.h"
#include "CrazyEngine/Graphics/TextureFont.h"

#include "CrazyEngine/Math/Rectangle.h"
#include "CrazyEngine/Math/Matrix4.h"

#define MAX_QUADS 1024
#define MAX_TEXTURE_SLOTS 32

namespace CrazyEngine
{
    class Renderer2D
    {
    private:

        RendererAPI* m_API;

        VertexArray* m_VertexArray;
        VertexBuffer* m_VertexBuffer;
        IndexBuffer* m_IndexBuffer;

        std::array<Texture*, MAX_TEXTURE_SLOTS> m_TextureSlots;
        std::uint32_t m_NextTextureIndex;

        Vertex* m_Vertices;
        Vertex* m_NextVertex;
        std::uint32_t m_IndexCount;

        Shader* m_Shader;

        Matrix4 m_ProjectionMatrix;

    public:
        Renderer2D();
        ~Renderer2D();

        void Initialise(const std::uint32_t width, const std::uint32_t height);
        void Terminate();

        void Begin();
        void End();

        void Resize(std::uint32_t width, std::uint32_t height);

        void Draw(const Rectangle& bounds, Texture* texture);
        void Draw(const Rectangle& bounds, const Rectangle& source, Texture* texture);

        void DrawString(const std::string& str, const Vector2& position, const Vector4& colour, TextureFont* font, float scale);
    };
}

#endif