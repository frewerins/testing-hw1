//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"

std::string url = "http://api.openweathermap.org/data/2.5/weather";
std::string forecastUrl = "http://api.openweathermap.org/data/2.5/forecast";
std::string city = "Moscow";

TEST(WeatherTestCase, test1) {
    cpr::Response response;
    response.status_code = 200;
    response.text = "{}";
    WeatherMock weather;
    ON_CALL(weather,
        Get(city, url)).WillByDefault(testing::Return(response));
    ASSERT_EQ(weather.GetResponseForCity(city, url), json::parse("{}"));
}

TEST(WeatherTestCase, test2) {
    cpr::Response response;
    response.status_code = 200;
    response.text = "{\"main\": {\"temp\":56}}";
    WeatherMock weather;
    ON_CALL(weather,
        Get(city, url)).WillByDefault(testing::Return(response));
    ASSERT_EQ(weather.GetTemperature(city), 56);
}

TEST(WeatherTestCase, test3) {
    cpr::Response response;
    response.status_code = 200;
    response.text = "{\"main\": {\"temp\":20}}";

    WeatherMock weather;
    ON_CALL(weather,
        Get("1", url)).WillByDefault(testing::Return(response));

    cpr::Response response2;
    response2.status_code = 200;
    response2.text = "{\"main\": {\"temp\":5}}";
    ON_CALL(weather,
        Get("2", url)).WillByDefault(testing::Return(response2));

    ASSERT_EQ(weather.FindDiffBetweenTwoCities("1", "2"), 20 - 5);
    ASSERT_EQ(weather.GetDifferenceString("2", "1"), "Weather in 2 is colder than in 1 by 15 degrees");
    ASSERT_EQ(weather.GetDifferenceString("1", "2"), "Weather in 1 is warmer than in 2 by 15 degrees");
}


TEST(WeatherTestCase, test4) {
    cpr::Response response;
    response.status_code = 200;
    response.text = "{\"list\":[{},{},{},{},{},{},{},{\"main\": {\"temp\":56}}]}";
    WeatherMock weather;
    ON_CALL(weather,
        Get(city, forecastUrl)).WillByDefault(testing::Return(response));
    ASSERT_EQ(weather.GetTomorrowTemperature(city), 56);
}

TEST(WeatherTestCase, test5) {
    WeatherMock weather;

    cpr::Response response;
    response.status_code = 200;
    response.text = "{\"list\":[{},{},{},{},{},{},{},{\"main\": {\"temp\":9}}]}";

    ON_CALL(weather,
        Get("1", forecastUrl)).WillByDefault(testing::Return(response));

    cpr::Response response2;
    response2.status_code = 200;
    response2.text = "{\"main\": {\"temp\":5}}";
    ON_CALL(weather,
        Get("1", url)).WillByDefault(testing::Return(response2));

    cpr::Response response3;
    response3.status_code = 200;
    response3.text = "{\"list\":[{},{},{},{},{},{},{},{\"main\": {\"temp\":5}}]}";

    ON_CALL(weather,
        Get("2", forecastUrl)).WillByDefault(testing::Return(response3));

    cpr::Response response4;
    response4.status_code = 200;
    response4.text = "{\"main\": {\"temp\":9}}";
    ON_CALL(weather,
        Get("2", url)).WillByDefault(testing::Return(response4));

    cpr::Response response5;
    response5.status_code = 200;
    response5.text = "{\"list\":[{},{},{},{},{},{},{},{\"main\": {\"temp\":5}}]}";

    ON_CALL(weather,
        Get("3", forecastUrl)).WillByDefault(testing::Return(response5));

    cpr::Response response6;
    response6.status_code = 200;
    response6.text = "{\"main\": {\"temp\":7}}";
    ON_CALL(weather,
        Get("3", url)).WillByDefault(testing::Return(response6));

    cpr::Response response7;
    response7.status_code = 200;
    response7.text = "{\"list\":[{},{},{},{},{},{},{},{\"main\": {\"temp\":7}}]}";

    ON_CALL(weather,
        Get("4", forecastUrl)).WillByDefault(testing::Return(response7));

    cpr::Response response8;
    response8.status_code = 200;
    response8.text = "{\"main\": {\"temp\":5}}";
    ON_CALL(weather,
        Get("4", url)).WillByDefault(testing::Return(response8));

    cpr::Response response9;
    response9.status_code = 200;
    response9.text = "{\"list\":[{},{},{},{},{},{},{},{\"main\": {\"temp\":7}}]}";

    ON_CALL(weather,
        Get("5", forecastUrl)).WillByDefault(testing::Return(response9));

    cpr::Response response10;
    response10.status_code = 200;
    response10.text = "{\"main\": {\"temp\":7}}";
    ON_CALL(weather,
        Get("5", url)).WillByDefault(testing::Return(response10));


    ASSERT_EQ(weather.GetTomorrowDiff("1"), "The weather in 1 tomorrow will be much warmer than today.");
    ASSERT_EQ(weather.GetTomorrowDiff("2"), "The weather in 2 tomorrow will be much colder than today.");
    ASSERT_EQ(weather.GetTomorrowDiff("3"), "The weather in 3 tomorrow will be colder than today.");
    ASSERT_EQ(weather.GetTomorrowDiff("4"), "The weather in 4 tomorrow will be warmer than today.");
    ASSERT_EQ(weather.GetTomorrowDiff("5"), "The weather in 5 tomorrow will be the same than today.");
}

TEST(WeatherTestCase, test6) {
    Weather weather;
    weather.SetApiKey("77");
    ASSERT_THROW(weather.GetResponseForCity("Novokuznetsk", url), std::invalid_argument);
}