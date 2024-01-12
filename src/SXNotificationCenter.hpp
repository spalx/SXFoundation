/**
 * @file SXNotificationCenter.hpp
 * @brief Declaration of the SXNotificationCenter class.
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

#ifndef SXNotificationCenter_hpp
#define SXNotificationCenter_hpp

#include "SXObject.hpp"
#include "SXDictionary.hpp"
#include "SXSelector.hpp"
#include <mutex>

namespace spalx {

/**
 * @class SXNotificationCenter
 * @brief A notification dispatch mechanism that enables the broadcast of information to registered observers.
 * @note This class is intended for use in a multithreaded environment. Ensure proper synchronization when accessing shared instances.
 */
class SXNotificationCenter : public SXObject
{
public:
    /**
     * @brief Deleted copy constructor to enforce the singleton pattern.
     */
    SXNotificationCenter(const SXNotificationCenter&) = delete;
    
    /**
     * @brief Deleted copy assignment operator to enforce the singleton pattern.
     */
    SXNotificationCenter& operator=(const SXNotificationCenter&) = delete;
    
    /**
     * @brief Get the singleton instance of this class.
     * @return The unique instance of the notification center.
     */
    static SXNotificationCenter* defaultCenter();
    
    /**
     * @brief Adds an observer for a specific notification.
     * @param pSelector The callback function to be executed when the notification is posted.
     * @param pName The name of the notification to observe.
     */
    void addObserver(SXSelector<void(SXDictionary*)>* pSelector, const char* pName);
    
    /**
     * @brief Removes an observer for a specific notification.
     * @param pSelector The callback function previously added as an observer.
     * @param pName The name of the notification to stop observing.
     */
    void removeObserver(SXSelector<void(SXDictionary*)>* pSelector, const char* pName);
    
    /**
     * @brief Posts a notification to all registered observers.
     * @param pName The name of the notification to be posted.
     * @param pUserInfo An optional dictionary containing additional information about the notification.
     */
    void postNotification(const char* pName, SXDictionary* pUserInfo = nullptr);
    
private:
    static SXNotificationCenter* pInstance; /**< The singleton instance of the notification center. */
    static std::mutex mutex; /**< Mutex for thread-safe operations on the singleton instance. */
    
    SXDictionary* m_pObservers{nullptr}; /**< Dictionary of registered observers. */
    
    /**
     * @brief Default constructor.
     * @details Public instantiation of the notification center is not allowed. Use the single instance by calling the static method defaultCenter().
     */
    SXNotificationCenter();
    
    /**
     * @brief Destructor.
     */
    ~SXNotificationCenter();
};
    
} // namespace spalx

#endif // SXNotificationCenter_hpp
