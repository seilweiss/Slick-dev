#pragma once

#include "render/material.h"

#include <glm/glm.hpp>

#include <QList>

namespace Rws { class Geometry; }

namespace Slick {

    namespace Render {

        class Geometry
        {
        public:
            Geometry(Context* context, Rws::Geometry* data = nullptr);

            Rws::Geometry* data() const { return m_data; }
            void setData(Rws::Geometry* data);

            Material* material(int index) { return &m_materials[index]; }
            int materialCount() const { return m_materials.size(); }

            bool isPrelit() const { return m_prelit; }
            void setPrelit(bool prelit) { m_prelit = prelit; }

            bool modulatesMaterialColor() const { return m_modulateMatColor; }
            void setModulateMaterialColor(bool mod) { m_modulateMatColor = mod; }

            void render();

        private:
            struct Mesh
            {
                QList<glm::uint16> indices;
                QList<glm::vec4> modulatedColors;
                glm::vec4 lastMatColor;
            };

            Context* m_context;
            Rws::Geometry* m_data;
            QList<Material> m_materials;
            QList<glm::vec3> m_vertices;
            QList<glm::vec3> m_normals;
            QList<glm::vec4> m_colors;
            QList<glm::vec2> m_uvs;
            QList<Mesh> m_meshes;
            bool m_hasAlpha;
            bool m_prelit;
            bool m_modulateMatColor;

            void updateMeshColors(int index);
        };

    }

}
