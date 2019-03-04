package com.z;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ObjectNode;
import com.rabbitmq.client.Channel;

import java.io.IOException;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicBoolean;

public class Sender {


    public static void main(String[] argv) throws Exception {
        Channel channel = RabbitMqUtils.initChannel();
        ObjectMapper mapper = new ObjectMapper();
        AtomicBoolean state = new AtomicBoolean(false);
        Executors.newSingleThreadExecutor().execute(() -> {
            while (true){
                try {
                    state.set(!state.get());
                    ObjectNode json = mapper.createObjectNode();
                    json.put("state",state.get());
                    RabbitMqUtils.sendTo(channel, RabbitMqUtils.RabbitTopic.LED,mapper.writeValueAsString(json));
                    Thread.sleep(5000);
                } catch (IOException | InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
    }
}

