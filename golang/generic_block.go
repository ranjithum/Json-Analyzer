package main

import (
	"bytes"
	"fmt"
)

type PrintPacketBlock struct {
}

func (pp *PrintPacketBlock) EvaluateBlock() bool {
	return true
}

func (pp *PrintPacketBlock) ToString() string {
	return "pp"
}

func (pp *PrintPacketBlock) AddCodeBlocks(blk GenericBlock) {
	panic("This is a leaf statement.. No one is supposed to call this")
}

func (pp *PrintPacketBlock) CleanUp() {
}

func (pp *PrintPacketBlock) SetJsonDecoder(dec JsonByteDecoderInterface) {
}

func NewPrintPacketBlock() *PrintPacketBlock {
	return &PrintPacketBlock{}
}

type IfBlock struct {
	m_lhsExpression GenericExpression
	m_rhsValue      *CompareValue
	m_codeBlocks    *listOfCodeBlocks
}

func (ifblk *IfBlock) EvaluateBlock() bool {
	lhs_v := ifblk.m_lhsExpression.GetValue()
	rhs_v := ifblk.m_rhsValue.m_rhsValue
	fmt.Print(lhs_v, " "+ifblk.m_rhsValue.m_comparator.ToString()+" ", rhs_v)

	if ifblk.m_rhsValue.CompareIt(lhs_v) {
		fmt.Println(" : Passed")
		for _, eachBlk := range *ifblk.m_codeBlocks {
			// fmt.Println(eachBlk.ToString())
			if eachBlk.EvaluateBlock() {
				return true
			}
		}
		return true
	}
	fmt.Println(" : Failed")
	return false
}

func (ifblk *IfBlock) AddCodeBlocks(blk GenericBlock) {
	ifblk.m_codeBlocks.AppendCodeBlock(blk)
}

func (ifblk *IfBlock) ToString() string {
	var if_blk_string bytes.Buffer
	if_blk_string.WriteString("if ")
	if_blk_string.WriteString(ifblk.m_lhsExpression.ToString())
	if_blk_string.WriteString(" " + ifblk.m_rhsValue.m_comparator.ToString())
	if_blk_string.WriteString(" " + ifblk.m_rhsValue.ToString())
	if_blk_string.WriteString(" {\n")
	if_blk_string.WriteString(ifblk.m_codeBlocks.ToString())
	if_blk_string.WriteString("\n}\n")
	return if_blk_string.String()
}

func (ifblk *IfBlock) CleanUp() {
}

func (ifblk *IfBlock) SetJsonDecoder(dec JsonByteDecoderInterface) {
	ifblk.m_lhsExpression.SetJsonDecoder(dec)
	for _, eachBlk := range *ifblk.m_codeBlocks {
		eachBlk.SetJsonDecoder(dec)
	}
}

func NewIfBlock(lhsExpr GenericExpression, rhs *CompareValue) *IfBlock {
	return &IfBlock{
		m_lhsExpression: lhsExpr,
		m_rhsValue:      rhs,
		m_codeBlocks:    NewListOfCodeBlock(),
	}
}

type ForBlock struct {
	m_lhsIdentifier string
	m_rhsExpression GenericExpression
	m_codeBlocks    *listOfCodeBlocks
}

func (forblk *ForBlock) EvaluateBlock() bool {
	return true
}

func (forblk *ForBlock) AddCodeBlocks(blk GenericBlock) {
	forblk.m_codeBlocks.AppendCodeBlock(blk)
}

func (forblk *ForBlock) ToString() string {
	var for_blk_string bytes.Buffer
	for_blk_string.WriteString("for ")
	for_blk_string.WriteString(forblk.m_lhsIdentifier)
	for_blk_string.WriteString(" in ")
	for_blk_string.WriteString(forblk.m_rhsExpression.ToString())
	for_blk_string.WriteString(" {\n")
	for_blk_string.WriteString(forblk.m_codeBlocks.ToString())
	for_blk_string.WriteString("\n}\n")
	return for_blk_string.String()
}

func (forblk *ForBlock) CleanUp() {
}

func (forblk *ForBlock) SetJsonDecoder(dec JsonByteDecoderInterface) {
	forblk.m_rhsExpression.SetJsonDecoder(dec)
	for _, eachBlk := range *forblk.m_codeBlocks {
		eachBlk.SetJsonDecoder(dec)
	}
}

func NewForBlock(lhs_ident string, rhs GenericExpression) *ForBlock {
	return &ForBlock{
		m_lhsIdentifier: lhs_ident,
		m_rhsExpression: rhs,
		m_codeBlocks:    NewListOfCodeBlock(),
	}
}
