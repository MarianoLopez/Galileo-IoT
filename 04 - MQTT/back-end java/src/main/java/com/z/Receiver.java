package com.z;

import com.rabbitmq.client.Channel;


public class Receiver {

    private static final String QUEUE_NAME = "java-temperature";

    public static void main(String[] argv) throws Exception {
        Channel channel1 = RabbitMqUtils.initChannel();
        RabbitMqUtils.subscribeTo(channel1,QUEUE_NAME, RabbitMqUtils.RabbitTopic.TEMPERATURE,RabbitMqUtils.getDefaultCallBack(channel1));
    }
}
