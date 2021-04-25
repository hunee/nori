[Lua] C와의 사용법


//-- get global environment table from registry
lua_rawgeti(pLuaState, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);

//-- create table containing the hook details
lua_newtable(pLuaState);
lua_pushstring(pLuaState, "__index");
lua_pushcfunction(pLuaState, function_hook);
lua_settable(pLuaState, -3);

//-- set global index callback hook
lua_setmetatable(pLuaState, -2);

//-- remove the global environment table from the stack
lua_pop(pLuaState, 1);



1. lua list
table 을 list 처럼 사용할 수 있다.
-- create
list = nil
for line in io.lines() do
    list = { next=list, value=line }
end

-- iterate
l = list
while l do
    print(l.value)
    l = l.next
end
2. C 에서 루아 변수 접근하기
string getString(lua_State* L, const string& variable)
{
    lua_pushstring(L, variable.c_str());
    lua_rawget(L, LUA_GLOBALSINDEX);

    if (!lua_isstring(L, -1))
        Assert(false);

    string rvalue = string(lua_tostring(L, -1));
    lua_pop(L, 1);
    return rvalue;
}

void setString(lua_State* L, const string& variable, const string& value)
{
    string command = variable + " = \"" + value + "\"";
    dobuffer(L, command, "setString");
}
3. 루아에서 C 변수 접근하기
루아에서 C 변수에 접근하는 것은 함수를 이용하면 비교적 간단하게 할 수 있다.
int gettext(lua_State *L)
{
    lua_pushstring(L, "this is first");
    return 1;   // 반환값이 1개
}
위의 함수를 등록하고, 이제 루아 상에서는 다음과 같이 실행한다.
a = gettext()
print(a)
두 개 이상의 값을 액세스하고자 할 때는 다음과 같이 하면 된다.
int gettext(lua_State *L)
{
    lua_pushstring(L, "this is first");
    lua_pushstring(L, "this is second");
    return 2;   // 반환값이 2개라는 의미.
}
a, b = gettext()
print(a, b)
4. C 에서 루아 테이블 생성하기
void createTable(lua_State* L, const string& tablename, const list& keys)
{
    // 빈 테이블을 생성한다.
    lua_newtable(L);

    // 각각의 키를 생성한다.
    // 키에 해당하는 값은 일단 숫자 0으로 세팅.
    list::const_iterator itr = keys.begin();
    for (; itr != keys.end(); itr++)
    {
        lua_pushstring(L, (*itr).c_str());
        lua_pushnumber(L, 0);
        lua_rawset(L, -3);
    }

    // 루아 table 모듈의 table.getn()함수 (테이블의 크기를 알아내는 함수)를
    // 위해서 n 변수를 설정해둔다.
    lua_pushstring(L, "n");
    lua_pushnumber(L, (int)(keys.size()));
    lua_rawset(L, -3);

    // 테이블을 전역 변수로 등록해서 다른 곳에서 액세스할 수 있도록 한다.
    lua_setglobal(L, tablename.c_str());
}
5. C 에서 루아 테이블 얻어오기
void getTable(lua_State* L, const string& tablename, map& pairs)
{
    pairs.clear();

    lua_pushstring(L, tablename.c_str());
    lua_rawget(L, LUA_GLOBALSINDEX);

    lua_pushnil(L);  // 첫번째 키부터 iteration하도록 설정
    while (lua_next(L, -2) != 0) 
    {
        string key = "";
        string value = "";

        // key는 stack[-2]에 있고, value는 stack[-1]에 있다.
        Assert(lua_type(L, -2) == LUA_TSTRING);
        key = string(lua_tostring(L, -2));

        switch (lua_type(L, -1))
        {
            case LUA_TNUMBER:
                value = MUtil::itos((int)lua_tonumber(L, -1));
                break;
            case LUA_TSTRING:
                value = string(lua_tostring(L, -1));
                break;
            default:
                NEVER_GET_HERE;
        }

        pairs[key] = value;

        // 키에 쌍이 되는 값(value)만 제거한다.
        // 다음 iteration 실행을 위해 현재 key값은 남겨둔다.
        lua_pop(L, 1); 
    }
}
6. C 에서 루아 테이블 내부값 건드리기
int getTableInt(lua_State* L, const string table, const string& index)
{
    lua_pushstring(L, table.c_str());
    lua_rawget(L, LUA_GLOBALSINDEX);

    lua_pushstring(L, index.c_str());
    lua_gettable(L, -2);

    if (!lua_isnumber(L, -1))
        Assert(false);

    int rvalue = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);
    return rvalue;
}

string getTableString(lua_State* L, const string table, const string& index)
{
    lua_pushstring(L, table.c_str());
    lua_rawget(L, LUA_GLOBALSINDEX);

    lua_pushstring(L, index.c_str());
    lua_gettable(L, -2);

    if (!lua_isstring(L, -1))
        Assert(false);

    string rvalue = string(lua_tostring(L, -1));
    lua_pop(L, 1);
    return rvalue;
}

void setTableInt(lua_State* L, const string table, const string& index, int value)
{
    lua_pushstring(L, table.c_str());
    lua_rawget(L, LUA_GLOBALSINDEX);

    lua_pushstring(L, index.c_str());
    lua_pushnumber(L, value);
    lua_settable(L, -3);

    lua_pop(L, 1);
}

void setTableString(lua_State* L, const string table, const string& index, const string& value)
{
    lua_pushstring(L, table.c_str());
    lua_rawget(L, LUA_GLOBALSINDEX);

    lua_pushstring(L, index.c_str());
    lua_pushstring(L, value.c_str());
    lua_settable(L, -3);

    lua_pop(L, 1);
}
7. 루아 테이블 -> 벡터,맵
// 스택의 최상단에 있는 값을 주어진 vector 변수에다 쓴다.
// 최상단에 있는 값이 적당한 타입이면 true를, 그렇지 않다면 false를 리턴.
// 값을 쓴 다음에는 스택에 있는 값을 pop해버린다.
bool LuaAPI::popVector(lua_State* L, vector& value)
{
    if (!lua_istable(L, -1)) return false;

    lua_pushnil(L); // 첫번째 키부터 iteration하도록 설정
    while (lua_next(L, -2) != 0)
    {
        // key는 stack[-2]에 있고, value는 stack[-1]에 있다.
        switch (lua_type(L, -1))
        {
            case LUA_TNUMBER:
                value.push_back(MUtil::itos((int)lua_tonumber(L, -1)));
                break;
            case LUA_TSTRING:
                value.push_back(string(lua_tostring(L, -1)));
                break;
            default:
                break;
        }

        // 키에 쌍이 되는 값(value)만 제거한다.
        // 다음 iteration 실행을 위해 현재 key값은 남겨둔다.
        lua_pop(L, 1);
    }

    lua_pop(L, 1); // 테이블을 pop해준다.

    return true;
}

// 스택의 최상단에 있는 값을 주어진 map 변수에다 쓴다.
// 최상단에 있는 값이 적당한 타입이면 true를, 그렇지 않다면 false를 리턴.
// 값을 쓴 다음에는 스택에 있는 값을 pop해버린다.
bool LuaAPI::popMap(lua_State* L, map& value)
{
    if (!lua_istable(L, -1)) return false;

    lua_pushnil(L); // 첫번째 키부터 iteration하도록 설정
    while (lua_next(L, -2) != 0)
    {
        // key는 stack[-2]에 있고, value는 stack[-1]에 있다.
        string key, val;

        switch (lua_type(L, -2))
        {
            case LUA_TNUMBER:
                key = MUtil::itos((int)lua_tonumber(L, -2));
                break;
            case LUA_TSTRING:
                key = string(lua_tostring(L, -2));
                break;
            default:
                break;
        }

        switch (lua_type(L, -1))
        {
            case LUA_TNUMBER:
                val = MUtil::itos((int)lua_tonumber(L, -1));
                break;
            case LUA_TSTRING:
                val = string(lua_tostring(L, -1));
                break;
            default:
                break;
        }

        value.insert(map::value_type(key, val));

        // 키에 쌍이 되는 값(value)만 제거한다.
        // 다음 iteration 실행을 위해 현재 key값은 남겨둔다.
        lua_pop(L, 1);
    }

    lua_pop(L, 1); // 테이블을 pop해준다.

    return true;
}
8. 벡터, 맵 -> 루아 테이블
// 스택의 최상단에다 벡터를 push한다.
void LuaAPI::pushVector(lua_State* L, const vector& value)
{
    // 빈 테이블을 생성해 스택의 맨 위에다 놓고...
    lua_newtable(L);
   
    for (size_t i=0; i& value)
{
    // 빈 테이블을 생성해 스택의 맨 위에다 놓고...
    lua_newtable(L);

    for (map::const_iterator itr = value.begin();
        itr != value.end(); itr++)
    {
        lua_pushstring(L, itr->first.c_str());  // key를 스택에 놓고...
        lua_pushstring(L, itr->second.c_str()); // value를 스택에 놓는다.
        lua_rawset(L, -3);
    }

    // 루아 table 모듈의 table.getn()함수 (테이블의 크기를 알아내는 함수)를
    // 위해서 n 변수를 설정해둔다. --주석처리:뭔가 이상하게 돌아간다.
    //lua_pushstring(L, "n");
    //lua_pushnumber(L, (int)(value.size()));
    //lua_rawset(L, -3);
}
9. C 에서 루아 함수 호출하기
luatest.lua
-- luatest.lua
function luafunction(num1, num2)
   return num1 + num2
end
main.c
int main(int argc, char *argv[]) 
{ 
    lua_State *L = lua_open(); // 루아 state를 생성한다. 
   
    lua_baselibopen(L); // print 루아 함수때문에 실행합니다. 나머지는 실행하면 스택만 길어지므로 빼주시길... 
   
    // luatest.lua 를 로드해서 실행한다. (5.0 beta에서만 됩니다. alpha에서는 에러! 버그였는데 해결된거더군요.) 
    lua_dofile (L, "luatest.lua"); 
   
    // "print(func1(100, 20))" 문장을 실행한다. 
    char tmpluacode[] = "print(luafunction(100, 20))";
    lua_dobuffer(L, tmpluacode, strlen(tmpluacode), "_temp"); 
   
    lua_close(L); // 루아 state를 해제한다. 
    return 0; 
} 
10. 루아에서 C 함수 호출하기
C에서 주어진 숫자들의 합을 리턴하는 함수를 작성하고, 이걸 루아에서 호출하려면 다음과 같이 할 수 있다.
main.c
int getsum(lua_State* L)
{
    int n = lua_gettop(L);    /* 인자의 개수 */
    lua_Number sum = 0;
    for (int i = 1; i <= n; i++) 
    {
        if (!lua_isnumber(L, i)) 
        {
            lua_pushstring(L, "incorrect argument to function `average'");
            lua_error(L);
        }

        sum += lua_tonumber(L, i);
    }
    lua_pushnumber(L, sum);
    return 1;
}

int main(int argc, char *argv[]) 
{ 
    lua_State *L = lua_open();
    lua_baselibopen(L);
    lua_register(L, "getsum", getsum);
    lua_dofile(L, "luatest.lua"); 

    char tmpluacode[] = "print(luafunction(100, 20))"; 
    lua_dobuffer(L, tmpluacode, strlen(tmpluacode), "_temp"); 

    lua_close(L);
    return 0; 
} 
luatest.lua
-- luatest.lua
function luafunction(num1, num2)
    return getsum(num1, num2)
end
11. 루아와 C++ 클래스의 연동
먼저 해당하는 클래스의 주소를 루아의 스택에다가 집어넣는다.
class Sample
{
private:
    lua_State* m_pLuaState;
    string     m_Name;

public:
    Sample()
    {
        ...
        setLuaInt(m_pLuaState, "systemAddress", (int)this);
    }
...

public:
    void executeEvent_1() { cout << "My name is " << m_Name << endl; }
    void executeEvent_2() { cout << "Ah... this is event 2!" << endl; }
}
그 다음 클래스 함수의 래퍼 함수를 만든다.
int handleEvent_1(lua_State* L)
{
    Sample* pSample = (Sample*)(getLuaInt(L, "systemAddress"));
    pSample->executeEvent_1();
    return 0;
}

int handleEvent_2(lua_State* L)
{
    Sample* pSample = (Sample*)(getLuaInt(L, "systemAddress"));
    pSample->executeEvent_2();
    return 0;
}
만든 래퍼 함수들을 루아에 등록해둔다.
Sample::Sample()
{
    ...
    lua_pushcfunction(m_pLuaState, handleEvent_1);
    lua_setglobal(m_pLuaState, "handleEvent_1");
    lua_pushcfunction(m_pLuaState, handleEvent_2);
    lua_setglobal(m_pLuaState, "handleEvent_2");
    ...
}
루아 소스에서 래퍼 함수를 호출한다.
    ...
    answer = getline();
    if (answer == "1") then
        handleEvent_1()
    elseif
        handleEvent_2()
    end
    ...
12. lua_State의 메모리 소모량
256메가 메모리를 가진 시스템에서 3000개 정도까지 무사히 생성되는 것을 확인했다. 순수하게 lua_open() 함수만을 이용해서 테스트한 것은 아니고, 따로 만들어진 커스텀 클래스의 생성을 테스트했다. 커스텀 클래스는 각종 멤버 변수 외에도 기본적인 아래의 루아 함수들을 스택에다 로드하는 클래스였다. 그리고 디버그 버전이었다. 어쨌든 3000개 정도를 생성했을 때 메모리 소모량은 87.5메가 정도였다. 환산해 보면 87,500,000 bytes / 3,000 = 29166 bytes = 29kbyte 정도있다. 꽤 큰 것 같기도 한데... 프로그램이 1기가 정도의 메모리를 가진 플랫폼에서 돌아간다고 가정하면 납득할 만하다고 생각한다.
systemQuestion = "";
systemAnswer = "";
systemMessage = "";
systemUserInputList = {};

function enqueueUserInput(userinput)
    table.insert(systemUserInputList, userinput);
end

function ask(...)
    local i = 1;
    while i <= arg.n do
        if i == 1 then
            systemQuestion = arg[i];
        else
            systemAnswer = systemAnswer .. "|" .. arg[i];
        end
        i = i + 1;
    end
   
    --print(systemQuestion);
    --print(systemAnswer);
   
    while true do
        -- 버퍼에 들어있는 유저 입력이 없다면
        -- 클라이언트에게 패킷을 보내라고 알려주고
        -- 실행을 중지한다.
        if (table.getn(systemUserInputList) == 0) then
            emitRequest();
            coroutine.yield("");
        -- 버퍼에 입력이 있다면 리턴하면 된다.
        -- 리턴하기 전에 버퍼에서 지워야한다.
        else
            local return_value = systemUserInputList[1];
            table.remove(systemUserInputList, 1);
            return return_value;
        end
    end
   
    return "";
end

function say(message)
    systemMessage = message;
    emitChatReply();
end