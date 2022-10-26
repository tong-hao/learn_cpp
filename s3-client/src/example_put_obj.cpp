#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/DeleteBucketRequest.h>
#include <aws/s3/model/DeleteObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>

/**
 * Before running this C++ code example, set up your development environment,
 * including your credentials.
 *
 * For more information, see the following documentation topic:
 *
 * https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/getting-started.html
 *
 * Purpose
 *
 * Demonstrates using the AWS SDK for C++ to put an object in an S3 bucket.
 *
 */

bool ListBuckets(const Aws::Client::ClientConfiguration &clientConfig) {
	Aws::S3::S3Client client(clientConfig);

	auto outcome = client.ListBuckets();

	bool result = true;
	if (!outcome.IsSuccess()) {
		std::cerr << "Failed with error: " << outcome.GetError() << std::endl;
		result = false;
	} else {
		std::cout << "Found " << outcome.GetResult().GetBuckets().size()
		          << " buckets\n";
		for (auto &&b : outcome.GetResult().GetBuckets()) {
			std::cout << b.GetName() << std::endl;
		}
	}

	return result;
}

//! Routine which demonstrates putting an object in an S3 bucket.
/*!
  \fn PutObject()
  \param bucketName Name of the bucket.
  \param fileName Name of the file to put in the bucket.
  \param clientConfig Aws client configuration.
*/

// snippet-start:[s3.cpp.put_object.code]
bool PutObject(const Aws::String &bucketName, const Aws::String &fileName,
               const Aws::Client::ClientConfiguration &clientConfig) {
	Aws::S3::S3Client s3_client(clientConfig);

	Aws::S3::Model::PutObjectRequest request;
	request.SetBucket(bucketName);
	// We are using the name of the file as the key for the object in the
	// bucket. However, this is just a string and can be set according to your
	// retrieval needs.
	request.SetKey(fileName);

	std::shared_ptr<Aws::IOStream> inputData = Aws::MakeShared<Aws::FStream>(
	    "SampleAllocationTag", fileName.c_str(),
	    std::ios_base::in | std::ios_base::out | std::ios_base::binary);

	if (!*inputData) {
		std::cerr << "Error unable to read file " << fileName << std::endl;
		return false;
	}

	request.SetBody(inputData);

	Aws::S3::Model::PutObjectOutcome outcome = s3_client.PutObject(request);

	if (!outcome.IsSuccess()) {
		std::cerr << "Error: PutObject: " << outcome.GetError().GetMessage()
		          << std::endl;
	} else {
		std::cout << "Added object '" << fileName << "' to bucket '"
		          << bucketName << "'.";
	}

	return outcome.IsSuccess();
}

bool PutObjectBuffer(const Aws::String &bucketName,
                     const Aws::String &objectName,
                     const std::string &objectContent,
                     const Aws::Client::ClientConfiguration &clientConfig) {
	Aws::S3::S3Client s3_client(clientConfig);

	Aws::S3::Model::PutObjectRequest request;
	request.SetBucket(bucketName);
	request.SetKey(objectName);

	const std::shared_ptr<Aws::IOStream> inputData =
	    Aws::MakeShared<Aws::StringStream>("");
	*inputData << objectContent.c_str();

	request.SetBody(inputData);

	Aws::S3::Model::PutObjectOutcome outcome = s3_client.PutObject(request);

	if (!outcome.IsSuccess()) {
		std::cerr << "Error: PutObjectBuffer: "
		          << outcome.GetError().GetMessage() << std::endl;
	} else {
		std::cout << "Success: Object '" << objectName << "' with content '"
		          << objectContent << "' uploaded to bucket '" << bucketName
		          << "'.";
	}

	return outcome.IsSuccess();
}

bool GetObject(const Aws::String &objectKey, const Aws::String &fromBucket,
               const Aws::Client::ClientConfiguration &clientConfig) {
	Aws::S3::S3Client client(clientConfig);

	Aws::S3::Model::GetObjectRequest request;
	request.SetBucket(fromBucket);
	request.SetKey(objectKey);

	Aws::S3::Model::GetObjectOutcome outcome = client.GetObject(request);

	if (!outcome.IsSuccess()) {
		const Aws::S3::S3Error &err = outcome.GetError();
		std::cerr << "Error: GetObject: " << err.GetExceptionName() << ": "
		          << err.GetMessage() << std::endl;
	} else {
		std::cout << "Successfully retrieved '" << objectKey << "' from '"
		          << fromBucket << "'." << std::endl;
	}

	return outcome.IsSuccess();
}

bool DeleteObject(const Aws::String &objectKey, const Aws::String &fromBucket,
                  const Aws::Client::ClientConfiguration &clientConfig) {
	Aws::S3::S3Client client(clientConfig);
	Aws::S3::Model::DeleteObjectRequest request;

	request.WithKey(objectKey).WithBucket(fromBucket);

	Aws::S3::Model::DeleteObjectOutcome outcome = client.DeleteObject(request);

	if (!outcome.IsSuccess()) {
		auto err = outcome.GetError();
		std::cerr << "Error: DeleteObject: " << err.GetExceptionName() << ": "
		          << err.GetMessage() << std::endl;
	} else {
		std::cout << "Successfully deleted the object." << std::endl;
	}

	return outcome.IsSuccess();
}

bool ListObjects(const Aws::String &bucketName,
                 const Aws::Client::ClientConfiguration &clientConfig) {
	Aws::S3::S3Client s3_client(clientConfig);

	Aws::S3::Model::ListObjectsRequest request;
	request.WithBucket(bucketName);

	auto outcome = s3_client.ListObjects(request);

	if (!outcome.IsSuccess()) {
		std::cerr << "Error: ListObjects: " << outcome.GetError().GetMessage()
		          << std::endl;
	} else {
		Aws::Vector<Aws::S3::Model::Object> objects =
		    outcome.GetResult().GetContents();

		for (Aws::S3::Model::Object &object : objects) {
			std::cout << object.GetKey() << std::endl;
		}
	}

	return outcome.IsSuccess();
}

bool CreateBucket(const Aws::String &bucketName,
                  const Aws::Client::ClientConfiguration &clientConfig) {
	Aws::S3::S3Client client(clientConfig);
	Aws::S3::Model::CreateBucketRequest request;
	request.SetBucket(bucketName);

	// TODO(user): Change the bucket location constraint enum to your target
	// Region.
	if (clientConfig.region != "us-east-1") {
		Aws::S3::Model::CreateBucketConfiguration createBucketConfig;
		createBucketConfig.SetLocationConstraint(
		    Aws::S3::Model::BucketLocationConstraintMapper::
		        GetBucketLocationConstraintForName(clientConfig.region));
		request.SetCreateBucketConfiguration(createBucketConfig);
	}

	Aws::S3::Model::CreateBucketOutcome outcome = client.CreateBucket(request);
	if (!outcome.IsSuccess()) {
		auto err = outcome.GetError();
		std::cerr << "Error: CreateBucket: " << err.GetExceptionName() << ": "
		          << err.GetMessage() << std::endl;
	} else {
		std::cout << "Created bucket " << bucketName
		          << " in the specified AWS Region." << std::endl;
	}

	return outcome.IsSuccess();
}

bool DeleteBucket(const Aws::String &bucketName,
                  const Aws::Client::ClientConfiguration &clientConfig) {
	Aws::S3::S3Client client(clientConfig);

	Aws::S3::Model::DeleteBucketRequest request;
	request.SetBucket(bucketName);

	Aws::S3::Model::DeleteBucketOutcome outcome = client.DeleteBucket(request);

	if (!outcome.IsSuccess()) {
		const Aws::S3::S3Error &err = outcome.GetError();
		std::cerr << "Error: DeleteBucket: " << err.GetExceptionName() << ": "
		          << err.GetMessage() << std::endl;
	} else {
		std::cout << "The bucket was deleted" << std::endl;
	}

	return outcome.IsSuccess();
}

/**
 *
 * main function
 *
 * TODO(user): items: Set the following variables:
 * - bucketName: The name of the bucket.
 * - fileName: The name of the file to add.
 *
 */

#ifndef TESTING_BUILD

int main() {
	Aws::SDKOptions options;
	Aws::InitAPI(options);
	{
		// TODO(user): Change bucket_name to the name of a bucket in your
		// account.
		const Aws::String bucket_name = "tong-hao-test";
		// TODO(user): Create a file called "my-file.txt" in the local folder
		// where your executables are built to.
		const Aws::String object_name = "d1/file1";

		Aws::Client::ClientConfiguration clientConfig;
		// Optional: Set to the AWS Region in which the bucket was created
		// (overrides config file). clientConfig.region = "us-east-1";
		clientConfig.region = "oss-cn-beijing";
		clientConfig.endpointOverride = "oss-cn-beijing.aliyuncs.com/";

		ListBuckets(clientConfig);
		PutObjectBuffer(bucket_name, object_name, "a,b\nc,d", clientConfig);
		ListObjects(bucket_name, clientConfig);
		GetObject(object_name, bucket_name, clientConfig);
		// DeleteObject(object_name, bucket_name, clientConfig);
	}

	Aws::ShutdownAPI(options);

	return 0;
}

#endif  // TESTING_BUILD
