

template<class _Ty> inline void writeToBinStream(std::ostream& os, const _Ty& v);
template<class _Ty> inline void readFromBinStream(std::istream& is, _Ty& v);
template<class _Ty> inline _Ty readFromBinStream(std::istream& is);
 
template<class _Ty>
inline typename std::enable_if<std::is_fundamental<_Ty>::value>::type writeToBinStreamImpl(std::ostream& os, const _Ty& v)
{
    if (!os.write((const char*)&v, sizeof(_Ty))) 
        throw std::ios_base::failure(std::string{ "writing type '" } + typeid(_Ty).name() + "' failed");
}

template<class _Ty>
inline void writeToBinStreamImpl(std::ostream& os, const typename std::vector<_Ty>& v)
{
    writeToBinStream<uint32_t>(os, v.size());
    for (auto& e : v)
    {
        writeToBinStream(os, e);
    }
}
template<class _Ty1, class _Ty2>
inline void writeToBinStreamImpl(std::ostream& os, const typename std::pair<_Ty1, _Ty2>& v)
{
    writeToBinStream(os, v.first);
    writeToBinStream(os, v.second);
}

template<class _Ty1, class _Ty2>
inline void writeToBinStreamImpl(std::ostream& os, const typename std::map<_Ty1, _Ty2>& v)
{
    writeToBinStream<uint32_t>(os, v.size());
    for (auto& p : v)
    {
        writeToBinStream(os, p);
    }
}

template<class _Ty>
inline void writeToBinStreamImpl(std::ostream& os, const typename std::set<_Ty>& v)
{
    writeToBinStream<uint32_t>(os, v.size());
    for (auto& e : v)
    {
        writeToBinStream(os, e);
    }
}
 
template<class _Ty>
inline void writeToBinStreamImpl(std::ostream& os, const typename std::basic_string<_Ty>& v)
{
    writeToBinStream<uint32_t>(os, v.size());
    for (auto& e : v)
    {
        writeToBinStream(os, e);
    }
}



template<class _Ty>
inline void writeToBinStream(std::ostream& os, const _Ty& v)
{
    writeToBinStreamImpl(os, v);
}
 
template<class _Ty>
inline void readFromBinStream(std::istream& is, _Ty& v)
{
    readFromBinStreamImpl(is, v);
}
 
template<class _Ty>
inline _Ty readFromBinStream(std::istream& is)
{
    _Ty v;
    readFromBinStreamImpl(is, v);
    return v;
}




template<class _Ty>
inline typename std::enable_if<std::is_fundamental<_Ty>::value>::type readFromBinStreamImpl(std::istream& is, _Ty& v)
{
    if (!is.read((char*)&v, sizeof(_Ty))) throw std::ios_base::failure(std::string{ "reading type '" } +typeid(_Ty).name() + "' failed");
}
 
template<class _Ty>
inline void readFromBinStreamImpl(std::istream& is, typename std::vector<_Ty>& v)
{
    v.resize(readFromBinStream<uint32_t>(is));
    for (auto& e : v)
    {
        readFromBinStream(is, e);
    }
}
 
template<class _Ty>
inline void readFromBinStreamImpl(std::istream& is, typename std::set<_Ty>& v)
{
    size_t len = readFromBinStream<uint32_t>(is);
    v.clear();
    for (size_t i = 0; i < len; ++i)
    {
        v.emplace(readFromBinStream<_Ty>(is));
    }
}
 
template<class _Ty>
inline void readFromBinStreamImpl(std::istream& is, typename std::basic_string<_Ty>& v)
{
    v.resize(readFromBinStream<uint32_t>(is));
    for (auto& e : v)
    {
        readFromBinStream(is, e);
    }
}
 
template<class _Ty1, class _Ty2>
inline void readFromBinStreamImpl(std::istream& is, typename std::pair<_Ty1, _Ty2>& v)
{
    v.first = readFromBinStream<_Ty1>(is);
    v.second = readFromBinStream<_Ty2>(is);
}
 
 
template<class _Ty1, class _Ty2>
inline void readFromBinStreamImpl(std::istream& is, typename std::map<_Ty1, _Ty2>& v)
{
    size_t len = readFromBinStream<uint32_t>(is);
    v.clear();
    for (size_t i = 0; i < len; ++i)
    {
        v.emplace(readFromBinStream<std::pair<_Ty1, _Ty2>>(is));
    }
}