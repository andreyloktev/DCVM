#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <Windows.h>

//access_toke: AQAAAAACBOwDAAVEODrB-wFqbk_etvcqyc-uLho
//token_type: bearer

const utility::string_t YANDEX_OATH_HOST    = U("https://oauth.yandex.ru");

int main(int argv, const char **ppArgc)
{
    web::http::status_code statusCode = 200;
    utility::string_t response;

    pplx::task<void> bugReasonTask = pplx::create_task(
        []
        {
            web::http::client::http_client boClient(YANDEX_OATH_HOST);

            web::http::http_request request(web::http::methods::POST);
            request.headers().add(U("Host"), U("oauth.yandex.ru"));
            request.headers().add(U("Content-type"), U("application/x-www-form-urlencoded"));
            
            utf16string body = U("grant_type=authorization_code&code=2884410&client_id=c8d081cd444947008587f4a277a942b4&client_secret=dc1ea6049ef34a51a6ae06a2a7ad6e6f");
            request.set_body(body);

            web::uri_builder uriBuilder(U("/token"));
            /*uriBuilder.append_query(U("grant_type"), U("authorization_code"));
            uriBuilder.append_query(U("code"), U("9635913"));*/

            request.set_request_uri(uriBuilder.to_string());

            std::wcout << request.to_string() << std::endl;

            return boClient.request(request);
        }
    ).then(
        [](web::http::http_response response)
        {
            std::cout <<    "Status code: " << response.status_code() << std::endl;
            return response.extract_json();
        }
    ).then(
        [&response](web::json::value responseJson)
        {
            std::wcout << responseJson << std::endl;
        }
    );

    try
    {
        bugReasonTask.wait();
    }
    catch(std::exception &err)
    {
        std::cout << "Error" << std::endl;
    }

    return 0;
}