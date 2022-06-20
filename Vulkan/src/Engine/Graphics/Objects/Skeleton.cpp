#include "Skeleton.h"

// bool LoadMesh(const std::string&  )
// {
//     // Release the previously loaded mesh (if it exists)
//     Clear();
// 
//     // Create the VAO
//     glGenVertexArrays(1, &m_VAO);
//     glBindVertexArray(m_VAO);
// 
//     // Create the buffers for the vertices attributes
//     glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
// 
//     bool Ret = false;
// 
//     m_pScene = m_Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals |
//         aiProcess_FlipUVs);
// 
//     if (m_pScene) {
//         m_GlobalInverseTransform = m_pScene->mRootNode->mTransformation;
//         m_GlobalInverseTransform.Inverse();
//         Ret = InitFromScene(m_pScene, Filename);
//     }
//     else {
//         printf("Error parsing '%s': '%s'\n", Filename.c_str(), m_Importer.GetErrorString());
//     }
// 
//     // Make sure the VAO is not changed from the outside
//     glBindVertexArray(0);
// 
//     return Ret;
// }