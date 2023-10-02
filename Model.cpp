#include "Model.h"

Model::~Model()
{
	vertexResource_->Release();
}

void Model::Initialize(WindowAPI* winApp, DirectXCommon* dxComon, MyEngine* engine, TextureManager* texture)
{
	winApp_ = winApp;
	dxCommon_ = dxComon;
	engine_ = engine;
	texture_ = texture;

	modelData_ = LoadObjFile("Resources", "plane.obj");


	VertexBuffer();


}

void Model::Update()
{

}

void Model::Draw()
{
	//VBVを設定
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	//形状を設定。PS0にせっていしているものとはまた別。同じものを設定する
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	
	//描画
	dxCommon_->GetCommandList()->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);

}




ModelData Model::LoadObjFile(const std::string& directoryPath, const std::string& filename)
{
	//1.中で必要となる変数の宣言
	ModelData modelData_;	//構築するModelData
	std::vector<Vector4>positions_;	//位置
	std::vector<Vector3>normals_;	//法線
	std::vector<Vector2>texcoords_;	//テクスチャ座標
	std::string line;	//ファイルから読んだ1行を格納するもの

	//2.ファイルを開く
	std::ifstream file(directoryPath + "/" + filename);	//ファイルを開く
	assert(file.is_open());	//とりあえず開けなかったら止める

	//3.実際にファイルを読み、ModelDataを構築していく
	while (std::getline(file, line))
	{
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;

		if (identifier == "v")
		{
			Vector4 position;
			s >> position.x >> position.y >> position.z;
			positions_.push_back(position);
		}
		else if (identifier == "vt")
		{
			Vector2 texccoord;
			s >> texccoord.x >> texccoord.y;
			texcoords_.push_back(texccoord);
		}
		else if (identifier == "vn")
		{
			Vector3 normal;
			s >> normal.x >> normal.y >> normal.z;
			normals_.push_back(normal);
		}
		else if (identifier == "f")
		{
			//面は三角形限定。その他は未対応。
			for (int32_t faveVertex = 0; faveVertex < 3; ++faveVertex)
			{
				std::string vertexDefinition;
				s >> vertexDefinition;
				//頂点の要素へのIndexは「位置/UV/法線」で格納されているので、分解してIndexを取得する
				std::istringstream v(vertexDefinition);
				uint32_t elementIndices[3];
				for (int32_t element = 0; element < 3; ++element)
				{
					std::string index;
					std::getline(v, index, '/');	//区切りでインデックスを読んでいく
					elementIndices[element] = std::stoi(index);
				}
				//要素へのIndexから、実際の要素の値を取得して、頂点を構築する
				Vector4 position = positions_[elementIndices[0] - 1];
				Vector2 texcoord = texcoords_[elementIndices[1] - 1];
				Vector3 normal = normals_[elementIndices[2] - 1];
				VertexData vertex = { position,texcoord,normal };
				modelData_.vertices.push_back(vertex);
			}
		}
	}

	//4.ModelDataを返す

	return modelData_;
}

void Model::VertexBuffer()
{
	//頂点用リソースを作る
	vertexResource_ = engine_->CreateBufferResource(sizeof(VertexData) * modelData_.vertices.size());	
	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView_.SizeInBytes = UINT(sizeof(VertexData) * modelData_.vertices.size());
	//1頂点当たりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(VertexData);
	//書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
	//頂点データをリソースにコピー
	std::memcpy(vertexData_, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());	
}