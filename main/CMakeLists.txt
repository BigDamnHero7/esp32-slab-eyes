idf_component_register(SRCS "mood.cpp" "main.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES ssd1306 esp_driver_gpio esp_driver_i2c esp_timer esp_hw_support)
                    
