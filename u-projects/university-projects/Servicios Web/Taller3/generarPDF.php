<?php
require('fpdf.php');

class PDF extends FPDF
{
	// Cabecera de página
	function Header()
	{
		// Logo 
		$this->Image('images/ICTAC2015_Logo.png',110,10,80);
		// Times bold 15
		$this->SetFont('Times','B',35);
		// Salto de línea
		$this->Ln(20);
		$this->Ln(20);
		// Movernos a la derecha
		$this->Cell(125);
		// Título w h string border ln align (L C R) fill link
		$this->Cell(30,10,'CERTIFICATE',0,1,'C');
		
	}


	// Pie de página
	function Footer()
	{
		// Aqui se supone que van las imagenes :D

	}
}

function CrearNuevoPdf($pdf, $name, $docType, $id, $Rol){
	$text1 = 'The organizing committee certifies that ' . $name;
	$text2 = ' with ' . $docType . ' ' . $id;
	$text3 = ' participated as ' . $Rol;
	$text4 = ' in the 12th International Colloquium on Theoretical Aspects of Computing (ICTAC 2015), on October 29-31, 2015 at the Pontificia Universidad Javeriana Cali.';
	// Creación del objeto de la clase heredada
	
	$pdf->AliasNbPages();
	$pdf->AddPage('L');
	$pdf->SetFont('Times','',20);

	$pdf->Ln(20);
	$pdf->MultiCell(0,10,$text1 . $text2 . $text3 . $text4,0,'C');
	$pdf->Ln(20);

	$pdf->SetFont('Times','',16);
	$pdf->Cell(0,10,'_________________________________',0,2,'C');
	$pdf->Cell(0,10,utf8_decode('Gloria Inés Álvarez'),0,2,'C');
	$pdf->Cell(0,10,'Organizing Committee',0,2,'C');

	//$pdf->ln(10);
	//$pdf->Image('images/CNRS_logo.png',0,null,40);

	return $pdf;
}


?>
