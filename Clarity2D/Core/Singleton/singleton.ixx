module;
    #include "c2d_dx.h"
export module c2d.core.singleton;

export namespace c2d
{
    template <class T> class Singleton
    {
    private:
        static_assert(std::is_class_v<T>, "Only class or struct is supported!");

    protected:
        Singleton()  = default;
        ~Singleton() = default;

        Singleton(const Singleton&)            = delete;
        Singleton& operator=(const Singleton&) = delete;

        // 기존 const rvalue에서 non-const rvalue 삭제로 변경
        Singleton(Singleton&&)            = delete;
        Singleton& operator=(Singleton&&) = delete;

    public:
        static T* GetInstance() noexcept
        {
            static T instance;
            return &instance;
        }
    };
}