package com.z.datalogger;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Import;
import org.springframework.data.annotation.CreatedDate;
import org.springframework.data.annotation.Id;
import org.springframework.data.annotation.LastModifiedDate;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.mongodb.config.EnableMongoAuditing;
import org.springframework.data.mongodb.core.mapping.Document;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.repository.query.Param;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;
import springfox.documentation.spring.data.rest.configuration.SpringDataRestConfiguration;
import springfox.documentation.swagger2.annotations.EnableSwagger2WebMvc;

import java.time.LocalDateTime;
import java.util.List;

@SpringBootApplication
@EnableMongoAuditing
@EnableSwagger2WebMvc
@Import(SpringDataRestConfiguration.class)
public class DataLoggerApplication {
    public static void main(String[] args) { SpringApplication.run(DataLoggerApplication.class, args); }
}

@Document
@Data
@NoArgsConstructor
@AllArgsConstructor
class DataLogger {
    @Id
    private String id;
    private String device;
    private List<Measurement> measurements;
    @CreatedDate
    private LocalDateTime createdDate;
    @LastModifiedDate
    private LocalDateTime lastModifiedDate;
}

@Data
@NoArgsConstructor
class Measurement{
    private SensorType sensorType;
    private float value;
}
enum SensorType {TEMPERATURE, LIGHT}

@RepositoryRestResource(collectionResourceRel = "data", path = "data")
interface DataLoggerDAO extends MongoRepository<DataLogger, String> {
    Page<DataLogger> findByDevice(@Param("device") String device, Pageable pageable);
}


