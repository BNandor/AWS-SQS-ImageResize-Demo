#include <aws/core/Aws.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/ReceiveMessageRequest.h>
#include <aws/sqs/model/ReceiveMessageResult.h>
#include <aws/sqs/model/DeleteMessageRequest.h>
#include <iostream>
#include "resize.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

void ReceiveMessage(const Aws::String& queue_url)
{
    Aws::Client::ClientConfiguration client_cfg;
    client_cfg.requestTimeoutMs = 30000;
    Aws::SQS::SQSClient sqs(client_cfg);
    Aws::SQS::Model::ReceiveMessageRequest rm_req;
    rm_req.SetQueueUrl(queue_url);
    rm_req.SetMaxNumberOfMessages(1);

    auto rm_out = sqs.ReceiveMessage(rm_req);
    if (!rm_out.IsSuccess())
    {
        std::cout << "Error receiving message from queue " << queue_url << ": "
            << rm_out.GetError().GetMessage() << std::endl;
        return;
    }

    const auto& messages = rm_out.GetResult().GetMessages();
    if (messages.size() == 0)
    {
        std::cout << "No messages received from queue " << queue_url <<
            std::endl;
        return;
    }

    const auto& message = messages[0];
    std::string imageJson(message.GetBody().c_str(), message.GetBody().size());
    rapidjson::Document d;
    d.Parse(imageJson.c_str());
 
    rapidjson::Value& b64Val = d["image"];
    std::string base64Image = b64Val.GetString();

    rapidjson::Value& widthVal = d["width"];
    int width = widthVal.GetInt();

    rapidjson::Value& heightVal = d["height"];
    int height = heightVal.GetInt();

    std::cout<<"Received height"<<height<<" width"<<width<<std::endl;
    std::cout<<"Resized Image:"<<opencv_resize::resizeImage(base64Image, width, height);

    Aws::SQS::Model::DeleteMessageRequest dm_req;
    dm_req.SetQueueUrl(queue_url);
    dm_req.SetReceiptHandle(message.GetReceiptHandle());

    auto dm_out = sqs.DeleteMessage(dm_req);
    if (dm_out.IsSuccess())
    {
        std::cout << "Successfully deleted message " << message.GetMessageId()
            << " from queue " << queue_url << std::endl;
    }
    else
    {
        std::cout << "Error deleting message " << message.GetMessageId() <<
            " from queue " << queue_url << ": " <<
            dm_out.GetError().GetMessage() << std::endl;
    }
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: receive_message <queue_url>" << std::endl;
        return 1;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        Aws::String queue_url = argv[1];

        ReceiveMessage(queue_url);
    }
    Aws::ShutdownAPI(options);
    return 0;
}