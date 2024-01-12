/**
 * @file SXPoolManager.hpp
 * @brief Implementation of the SXPoolManager class.
 *
 * @copyright (c) 2024 Artavazd Barseghyan
 * @details This software is released under the MIT License.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "SXPoolManager.hpp"

namespace spalx {

SXPoolManager* SXPoolManager::pInstance = nullptr;
std::mutex SXPoolManager::mutex;

SXPoolManager* SXPoolManager::sharedPoolManager()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (!pInstance) {
        pInstance = new SXPoolManager();
    }
    
    return pInstance;
}

void SXPoolManager::purgePoolManager()
{
    if (pInstance) {
        delete pInstance;
        pInstance = nullptr;
    }
}

void SXPoolManager::push()
{
    SXAutoreleasePool* pPool = new SXAutoreleasePool();
    m_pCurrentPool = pPool;
    m_pPools->addObject(pPool);
    pPool->release();
}

void SXPoolManager::pop()
{
    if (m_pCurrentPool) {
        m_pPools->removeLastObject();
        m_pCurrentPool = dynamic_cast<SXAutoreleasePool*>(m_pPools->lastObject());
    }
}

void SXPoolManager::addObject(SXObject* pObject)
{
    m_pCurrentPool->addObject(pObject);
}

void SXPoolManager::removeObject(SXObject* pObject)
{
    m_pCurrentPool->removeObject(pObject);
}

SXPoolManager::SXPoolManager()
:m_pCurrentPool(nullptr)
{
    m_pPools = new SXArray();
    m_pPools->initWithCapacity(1);
    
    // Create and push an empty autorelease pool for the first time.
    push();
}

SXPoolManager::~SXPoolManager()
{
    if (m_pPools) {
        m_pPools->release();
        m_pPools = nullptr;
        m_pCurrentPool = nullptr;
    }
}

}
