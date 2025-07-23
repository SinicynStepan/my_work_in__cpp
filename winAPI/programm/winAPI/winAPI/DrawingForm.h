#pragma once
#include "Shape.h"


namespace winAPI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	public ref class DrawingForm : public System::Windows::Forms::Form
	{
	public:
		DrawingForm(ManagedShape ^shape, System::Double ^squeeze_value, System::Double ^stretch_value, System::Double ^rotate_value)
		{
			this->shape = shape;
			this->squeeze_value = squeeze_value;
			this->stretch_value = stretch_value;
			this->rotate_value = rotate_value;
			this->DoubleBuffered = true;

			InitializeComponent();
		}
	protected:
		~DrawingForm()
		{
			if (components)
				delete components;
		}
	private: 
		bool isWindowMoving;
		System::Windows::Forms::PictureBox ^pictureBox;
		System::ComponentModel::Container ^components;
		ManagedShape ^shape;
		System::Double ^squeeze_value;
		System::Double ^stretch_value;
		System::Double ^rotate_value;
		
	private:	System::Void drawing(System::Object ^sender, System::Windows::Forms::PaintEventArgs ^e);

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(0, 0);
			this->pictureBox->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(1182, 1160);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->pictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &DrawingForm::drawing);
			// 
			// DrawingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(1184, 1161);
			this->Controls->Add(this->pictureBox);
			this->DoubleBuffered = true;
			this->Name = L"DrawingForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ShapeDrawing";
			this->Load += gcnew System::EventHandler(this, &DrawingForm::DrawingForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void DrawingForm_Load(System::Object ^sender, System::EventArgs ^e){
		}
	};
}
