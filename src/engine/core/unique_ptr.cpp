#if 0

// default_delete 대신에 내가 작성한 delete를 사용합니다.
// 삭제된 객체의 갯수에 대해서 카운팅합니다. 
template <class _Ty>
struct My_delete { // default deleter for unique_ptr
    constexpr My_delete() noexcept = default;

    template <class _Ty2, std::enable_if_t<std::is_convertible_v<_Ty2*, _Ty*>, int> = 0>
    My_delete(const My_delete<_Ty2>&) noexcept {}

    void operator()(_Ty* _Ptr) const noexcept /* strengthened */ { // delete a pointer
        static_assert(0 < sizeof(_Ty), "can't delete an incomplete type");
        s_deleteCount.fetch_add(1);
        delete _Ptr;
    }
private:
    static std::atomic<DWORD> s_deleteCount;
};

template <class _Ty>
std::atomic<DWORD> My_delete<_Ty>::s_deleteCount;


// 실제 호출시 
std::unique_ptr<int, My_delete<int>> pUInt;
#endif

