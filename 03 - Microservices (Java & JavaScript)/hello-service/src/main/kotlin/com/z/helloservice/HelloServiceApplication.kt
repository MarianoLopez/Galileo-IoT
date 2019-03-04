package com.z.helloservice

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication
import org.springframework.cloud.client.discovery.DiscoveryClient
import org.springframework.cloud.netflix.eureka.EnableEurekaClient
import org.springframework.cloud.openfeign.EnableFeignClients
import org.springframework.cloud.openfeign.FeignClient
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.RestController

@SpringBootApplication
@EnableEurekaClient
@EnableFeignClients
@RestController
class HelloServiceApplication(val discoveryClient: DiscoveryClient, val galileoFeignClient: GalileoFeignClient){

    @GetMapping fun index() = "Hello World from hello-service"

    @GetMapping("/instances") fun instances(): List<String> = discoveryClient.services

    @GetMapping("/fahrenheit") fun fahrenheit():Temperature = galileoFeignClient.getTemperature().apply {
        temperature = (temperature * 9/5)+32
    }
}

@FeignClient("galileo-service")
interface GalileoFeignClient{
    @GetMapping("/temperature") fun getTemperature():Temperature
}

data class Temperature(var temperature:Float)

fun main(args: Array<String>) {
    runApplication<HelloServiceApplication>(*args)
}
